#include <QtTest>
#include "../../include/DataKeeperTree.h"

// add necessary includes here

class TestDataKeeperTree : public QObject
{
    Q_OBJECT

public:
    TestDataKeeperTree();
    ~TestDataKeeperTree();

private slots:
    void test_init_attr();
    void test_make_dump_attr();
    void test_from_dump_attr();
    void test_init_datakeeper();
    void test_datakeper_childs();
    void test_datakeper_make_dump();
    void test_datakeper_from_dump();
};

TestDataKeeperTree::TestDataKeeperTree()
{}

TestDataKeeperTree::~TestDataKeeperTree()
{}

void TestDataKeeperTree::test_init_attr()
{
    Attribute attr;
    Attribute attr_1(new QVariant("1"));
    Attribute attr_2("name");
    Attribute attr_3(new QVariant("3"),"Name");

    QCOMPARE(attr.is_root(), true);
    QCOMPARE(attr.get_name(),"");
    QCOMPARE(attr.is_valid(),false);

    QCOMPARE(attr_1.is_root(), false);
    QCOMPARE(attr_1.get_name(),"");
    QCOMPARE(attr_1.is_valid(),true);

    QCOMPARE(attr_2.is_root(), false);
    QCOMPARE(attr_2.get_name(),"name");
    QCOMPARE(attr_2.is_valid(),false);

    QCOMPARE(attr_3.is_root(), false);
    QCOMPARE(attr_3.get_name(),"Name");
    QCOMPARE(attr_3.is_valid(),true);

//    QTest::addColumn<bool>("Is root?");
//    QTest::addColumn<QString>("Value");
//    QTest::addColumn<QString>("Name");

//    QTest::newRow("attr")<<attr.is_root()<<((attr.get_val()==nullptr)? "":attr_2.get_val()->toString())<<QString::fromStdString(attr.get_name());
//    QTest::newRow("attr_1")<<attr_1.is_root()<<((attr_1.get_val()==nullptr)? "":attr_1.get_val()->toString())<<QString::fromStdString(attr_1.get_name());
//    QTest::newRow("attr_2")<<attr_2.is_root()<< ((attr_2.get_val()==nullptr)? "":attr_2.get_val()->toString())<<QString::fromStdString(attr_2.get_name());
    //    QTest::newRow("attr_3")<<attr_3.is_root()<<((attr_3.get_val()==nullptr)? "":attr_3.get_val()->toString())<<QString::fromStdString(attr_3.get_name());
}

void TestDataKeeperTree::test_make_dump_attr()
{
    Attribute attr;
    Attribute attr_1(new QVariant("1"));
    Attribute attr_2("name");
    Attribute attr_3(new QVariant("3"),"Name");

    std::string attr_dump = "/root,GeneratedName_0";
    std::string attr_1_dump = "/GeneratedName_1,1";
    std::string attr_2_dump = "/name";
    std::string attr_3_dump = "/name,3";

//    std::string nn = attr_1.make_dump_string();

    QCOMPARE(attr.make_dump_string(), attr_dump);
    QCOMPARE(attr_1.make_dump_string(), attr_1_dump);
    QCOMPARE(attr_2.make_dump_string(), attr_2_dump);
    QCOMPARE(attr_3.make_dump_string(), attr_3_dump);
}

void TestDataKeeperTree::test_from_dump_attr()
{


}

void TestDataKeeperTree::test_init_datakeeper()
{

}

void TestDataKeeperTree::test_datakeper_childs()
{

}

void TestDataKeeperTree::test_datakeper_make_dump()
{

}

void TestDataKeeperTree::test_datakeper_from_dump()
{

}

QTEST_APPLESS_MAIN(TestDataKeeperTree)

#include "tst_testdatakeepertree.moc"
