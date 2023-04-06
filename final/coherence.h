#ifndef COHERENCE_H
#define COHERENCE_H


class Coherence
{
public:
    Coherence();
    Coherence(int, int);
    
    int GetScore() {return score;}
    int GetLevel() {return level;}
    int GetAchievementScore() {return achievement_score;}
    
    void SetScore(int s) { score = s; }
    void SetLevel(int l) { level = l; }
    void AddToAchievement(int s) { achievement_score += s;}
    
private:
    int score;
    int level;
    int achievement_score;
};

#endif // COHERENCE_H
