#include <QtTest>
#include "score.hh"
// add necessary includes here

class Score_Test : public QObject
{
    Q_OBJECT

public:
    Score_Test();
    ~Score_Test();

private slots:
    void test_increase();
    void test_decrease();
};

Score_Test::Score_Test()
{

}

Score_Test::~Score_Test()
{

}

void Score_Test::test_increase()
{
    Score *s=new Score();
    s->increase();
    QCOMPARE(s->CurrentScore(),1);
    s->increase();
    s->increase();
    QCOMPARE(s->CurrentScore(),3);
}
void Score_Test::test_decrease()
{
    Score *s=new Score();

    s->decrease();
    s->decrease();
    QCOMPARE(s->CurrentScore(),-2);

    s->increase();
    s->increase();
    s->decrease();
    QCOMPARE(s->CurrentScore(),-1);
}

QTEST_APPLESS_MAIN(Score_Test)

#include "tst_score_test.moc"
