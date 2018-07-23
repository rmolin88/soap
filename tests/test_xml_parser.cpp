#include <fstream>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <sstream>
#include <string>
#include <iostream>

#include <libxml/parser.h>
#include <libxml/tree.h>

const std::string file("../xml/sample.xml");
std::ostringstream buff;

void print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;

	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			printf("node type: Element, name: %s\n", cur_node->name);
		}

		print_element_names(cur_node->children);
	}
}

TEST(LibXml2, XmlParsing){
    xmlDocPtr doc = xmlReadMemory(buff.str().c_str(), buff.str().length(), file.c_str(),
                                  nullptr, 0);
	ASSERT_NE(doc, nullptr);

	xmlNode *node = xmlDocGetRootElement(doc);

	print_element_names(node);

	xmlCleanupParser();
	xmlMemoryDump();
}

TEST(RapidXml, CreateDom) {
  rapidxml::xml_document<> doc;

  doc.parse<0>(buff.str().data());

  LOG(INFO) << "File (" << file << ") = \n" << doc;

  // rapidxml::xml_node<"NewStudentInfo"> *node =
  // doc.first_node("NewStudentInfo");

  rapidxml::xml_node<char> *node = doc.first_node();

  // LOG(INFO) << "Name of my first node is: " << doc.first_node()->name() <<
  // "\n";
  LOG(INFO) << "Node has value " << node->value() << "\n";
  for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr;
       attr = attr->next_attribute()) {
    LOG(INFO) << "\tNode foobar has attribute " << attr->name() << " ";
    LOG(INFO) << "\t\tWith value " << attr->value() << "\n";
  }
}

int main(int argc, char *argv[])
{
	FLAGS_logtostderr = 1;
	FLAGS_colorlogtostderr = 1;
	::google::InitGoogleLogging(argv[0]);
	::testing::InitGoogleTest(&argc, argv);

	LIBXML_TEST_VERSION

	std::ifstream ifs(file);
	if (ifs.is_open() == false)
	{
		std::cerr << "Failed to open file: " << file << "\n";
		return 1;
	}

	buff << ifs.rdbuf();

	if (buff.str().empty() == true)
	{
		std::cerr << "Opened file empty\n";
		return 2;
	}

	return RUN_ALL_TESTS();
}
