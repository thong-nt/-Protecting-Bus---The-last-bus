#include <QtTest>

// add necessary includes here

class Statistic_test : public QObject
{
    Q_OBJECT

public:
    Statistic_test();
    ~Statistic_test();

private slots:
    void test_case1();

};

Statistic_test::Statistic_test()
{

}

Statistic_test::~Statistic_test()
{

}

void Statistic_test::test_case1()
{

}

QTEST_APPLESS_MAIN(Statistic_test)

#include "tst_statistic_test.moc"
