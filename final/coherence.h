#ifndef COHERENCE_H
#define COHERENCE_H


class Coherence
{
public:
    Coherence();
    Coherence(int, int);
    
    int GetScore() {return score;}
    int GetLevel() {return level;}
    
    void SetScore(int s) { score = s; }
    void SetLevel(int l) { level = l; }
    
private:
    int score;
    int level;
};

#endif // COHERENCE_H
