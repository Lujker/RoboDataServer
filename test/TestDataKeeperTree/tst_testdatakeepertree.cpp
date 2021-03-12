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

};

TestDataKeeperTree::TestDataKeeperTree()
{

}

TestDataKeeperTree::~TestDataKeeperTree()
{

}

void TestDataKeeperTree::test_init_attr()
{
//    Attribute attr;
    DataKeeperTree dkt;

//    QTest::addColumn<bool>(attr.is_root());
    QCOMPARE(dkt.is_root(),true);

}

QTEST_APPLESS_MAIN(TestDataKeeperTree)

#include "tst_testdatakeepertree.moc"
