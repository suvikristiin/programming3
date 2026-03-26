#include <QtTest>
#include "../card.hh"
#include "../deck.hh"
#include "../utils.hh"
#include "../deckmanager.hh"

using namespace std;

class flashcardstest : public QObject
{
    Q_OBJECT

public:
    flashcardstest();
    ~flashcardstest();

private slots:
    void test_case1();
    void testAddCard();
    void testCopyCards();
    void check_answers();
    void check_answers_data();
};

flashcardstest::flashcardstest() {}

flashcardstest::~flashcardstest() {}

void flashcardstest::test_case1() {}


void flashcardstest::testAddCard() {
    vector<string> fields = {"Question", "Answer"};
    Deck d("TestDeck", fields);

    shared_ptr<Card> card = make_shared<Card>();
    vector<string> definitions = {"Capital of Finland?", "Helsinki"};

    QVERIFY(card->add_new_definitions(fields, definitions));
    QVERIFY(d.add_card(card));

    vector<unsigned int> ids = d.get_card_ids();
    QCOMPARE(ids.size(), size_t(1));
    QCOMPARE(ids[0], card->get_id());
}

void flashcardstest::testCopyCards() {
    std::vector<std::string> fields = {"Q", "A"};
    DeckManager deck_manager = DeckManager();
    shared_ptr<Deck> source = deck_manager.add_deck("SourceDeck", fields);
    shared_ptr<Deck> target = deck_manager.add_deck("TargetDeck", fields);

    shared_ptr<Card> card1 = make_shared<Card>();
    card1->add_new_definitions({"Q","A"}, {"1+1?","2"});
    shared_ptr<Card>  card2 = make_shared<Card>();
    card2->add_new_definitions({"Q","A"}, {"2+2?","4"});

    source->add_card(card1);
    source->add_card(card2);

    QVERIFY(deck_manager.copy("SourceDeck", "TargetDeck"));
    vector<unsigned int> target_ids = target->get_card_ids();
    vector<unsigned int> source_ids = source->get_card_ids();
    QCOMPARE(target_ids.size(), size_t(2));
    QCOMPARE(target_ids[0], source_ids[0]);
    QCOMPARE(target_ids[1], source_ids[1]);
    QCOMPARE(target_ids[0], card1->get_id());
    QCOMPARE(target_ids[1], card2->get_id());
}

void flashcardstest::check_answers_data()
{
    QTest::addColumn<Fields>("fields");
    QTest::addColumn<Fields>("user_answers");
    QTest::addColumn<double>("expected_score");

    // Luodaan testitapauksia
    QTest::newRow("all correct") << Fields{"EN","DE"}
                                 << Fields{"one","eins"}
                                 << 1.0;

    QTest::newRow("half correct") << Fields{"EN","DE"}
                                  << Fields{"one","wrong"}
                                  << 0.5;

    QTest::newRow("all wrong") << Fields{"EN","DE"}
                               << Fields{"wrong1","wrong2"}
                               << 0.0;

}

void flashcardstest::check_answers()
{
    QFETCH(Fields, fields);
    QFETCH(Fields, user_answers);
    QFETCH(double, expected_score);

    shared_ptr<Card> card = make_shared<Card>();
    bool ok = card->add_new_definitions({"EN","DE"},{"one","eins"});
    QVERIFY(ok);

    QVERIFY(card->has_fields(fields));


    double score = card->check_answers(fields, user_answers);

    QCOMPARE(score, expected_score);
}




QTEST_APPLESS_MAIN(flashcardstest)

#include "tst_flashcardstest.moc"
