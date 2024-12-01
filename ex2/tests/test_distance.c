#include "unity.h"
#include "distance.h"

// Variabili globali per i test
int **memo = NULL;
const int MAX_LEN = 19; // Lunghezza massima delle parole nel dizionario

// Setup: Inizializza la matrice di memoizzazione
void setUp(void) {
    memo = initialize_memo(MAX_LEN + 1, MAX_LEN + 1);
}

// Teardown: Libera la matrice di memoizzazione
void tearDown(void) {
    free_memo(memo, MAX_LEN + 1);
    memo = NULL;
}

// Test della funzione min3
void test_min3(void) {
    TEST_ASSERT_EQUAL_INT(1, min3(1, 2, 3));
    TEST_ASSERT_EQUAL_INT(0, min3(0, 5, 10));
    TEST_ASSERT_EQUAL_INT(-10, min3(-10, -5, 0));
    TEST_ASSERT_EQUAL_INT(5, min3(5, 5, 5)); // Tutti uguali
}

// Test della edit distance con stringhe vuote
void test_edit_distance_empty_strings(void) {
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(0, edit_distance("", "", memo));
    TEST_ASSERT_EQUAL_INT(5, edit_distance("", "abcde", memo)); // Lunghezza della seconda stringa
    TEST_ASSERT_EQUAL_INT(4, edit_distance("abcd", "", memo)); // Lunghezza della prima stringa
}

// Test della edit distance con stringhe identiche
void test_edit_distance_identical_strings(void) {
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(0, edit_distance("abc", "abc", memo));
}

// Test della edit distance con stringhe di diversa lunghezza
void test_edit_distance_different_lengths(void) {
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(1, edit_distance("abc", "abcd", memo));
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(1, edit_distance("abcd", "abc", memo));
}

// Test della edit distance con sostituzioni
void test_edit_distance_with_substitutions(void) {
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(3, edit_distance("abc", "def", memo)); // Tutti i caratteri diversi
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(1, edit_distance("abc", "adc", memo)); // Una sostituzione
}

// Test aggiornato della edit distance con parole lunghe
void test_edit_distance_long_words(void) {
    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(1, edit_distance("abcdefghijklmnopqrs", "abcdefghijklmnopqr", memo)); // Rimozione singola

    reset_memo(memo, MAX_LEN + 1, MAX_LEN + 1);
    TEST_ASSERT_EQUAL_INT(1, edit_distance("aaaaaaaaaaaaaaaaaaa", "aaaaaaaabaaaaaaaaaa", memo)); // Sostituzione singola
}


int main(void) {
    UNITY_BEGIN();

    // Aggiunta dei test
    RUN_TEST(test_min3);
    RUN_TEST(test_edit_distance_empty_strings);
    RUN_TEST(test_edit_distance_identical_strings);
    RUN_TEST(test_edit_distance_different_lengths);
    RUN_TEST(test_edit_distance_with_substitutions);
    RUN_TEST(test_edit_distance_long_words);

    return UNITY_END();
}
