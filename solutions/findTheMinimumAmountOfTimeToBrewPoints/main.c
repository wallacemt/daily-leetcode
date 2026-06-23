long long minTime(int* skill, int skillSize, int* mana, int manaSize) {
    int n = skillSize, m = manaSize;
    
    long long dp[n + 1];
    memset(dp, 0, sizeof(dp));
    
    const int* const skill_end = skill + n;
    const int* const mana_end = mana + m;
    
    for (const int* mana_ptr = mana; mana_ptr < mana_end; ++mana_ptr) {
        const long long current_mana = *mana_ptr;
        
        const int* skill_ptr = skill;
        for (int i = 0; i < n; ++i, ++skill_ptr) {
            long long gain = current_mana * (*skill_ptr);
            dp[i + 1] = (dp[i + 1] > dp[i] ? dp[i + 1] : dp[i]) + gain;
        }
        
        skill_ptr = skill + n - 1;
        for (int i = n - 1; i > 0; --i, --skill_ptr) {
            dp[i] = dp[i + 1] - current_mana * (*skill_ptr);
        }
    }
    
    return dp[n];
}
