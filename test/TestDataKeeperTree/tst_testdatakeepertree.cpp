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
    void test_init_attr_data();

};

TestDataKeeperTree::TestDataKeeperTree()
{}

TestDataKeeperTree::~TestDataKeeperTree()
{}

void TestDataKeeperTree::test_init_attr_data()
{
    Attribute attr;
    Attribute attr_1(new QVariant("1"));
    Attribute attr_2("name");
    Attribute attr_3(new QVariant("3"),"Name");

//    QTest::addColumn<bool>("Is root?");
//    QTest::addColumn<QString>("Value");
//    QTest::addColumn<QString>("Name");

//    QTest::newRow("attr")<<attr.is_root()<<((attr.get_val()==nullptr)? "":attr_2.get_val()->toString())<<QString::fromStdString(attr.get_name());
//    QTest::newRow("attr_1")<<attr_1.is_root()<<((attr_1.get_val()==nullptr)? "":attr_1.get_val()->toString())<<QString::fromStdString(attr_1.get_name());
//    QTest::newRow("attr_2")<<attr_2.is_root()<< ((attr_2.get_val()==nullptr)? "":attr_2.get_val()->toString())<<QString::fromStdString(attr_2.get_name());
//    QTest::newRow("attr_3")<<attr_3.is_root()<<((attr_3.get_val()==nullptr)? "":attr_3.get_val()->toString())<<QString::fromStdString(attr_3.get_name());
}

QTEST_APPLESS_MAIN(TestDataKeeperTree)

#include "tst_testdatakeepertree.moc"
