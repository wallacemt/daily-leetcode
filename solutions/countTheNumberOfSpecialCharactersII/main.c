int numberOfSpecialChars(char* word) {
    uint32_t lower = 0;
    uint32_t upper = 0;
    uint32_t invalid = 0;
    
    unsigned c;
    
    while ((c = (unsigned char)*word++)) {
        unsigned idx = c & 31;
        
        if (c & 32) {
            uint32_t bit = 1u << (idx - 1);
            invalid |= upper & bit;
            lower |= bit;
        } else {
            upper |= 1u << (idx - 1);
        }
    }
    
    return __builtin_popcount(lower & upper & ~invalid);
}