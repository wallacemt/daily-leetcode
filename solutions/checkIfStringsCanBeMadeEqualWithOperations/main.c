bool canBeEqual(char* s1, char* s2) 
{
    bool pos0_match = (s1[0] == s2[0] || s1[0] == s2[2]);
    bool pos2_match = (s1[2] == s2[2] || s1[2] == s2[0]);
    bool pos1_match = (s1[1] == s2[1] || s1[1] == s2[3]);
    bool pos3_match = (s1[3] == s2[3] || s1[3] == s2[1]);
    
    return pos0_match && pos2_match && pos1_match && pos3_match;
}