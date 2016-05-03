#ifndef RANDOM_LETTERS_H
#define RANDOM_LETTERS_H

class RandomLetters : public Effect{
  public:
    RandomLetters();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);

  private:
};
#endif
