int compareVersion(char* version1, char* version2) {
    int n1 = 0, n2 = 0;
    while (version1[n1] != '\0' || version2[n2] != '\0') {
        int v1 = 0, v2 = 0;
        while (version1[n1] != '\0' && version1[n1] != '.') {
            v1 = v1 * 10 + (version1[n1] - '0');
            n1++;
        }
        while (version2[n2] != '\0' && version2[n2] != '.') {
            v2 = v2 * 10 + (version2[n2] - '0');
            n2++;
        }
        if (v1 > v2) return 1;
        else if (v1 < v2) return -1;
        if (version1[n1] == '.') n1++;
        if (version2[n2] == '.') n2++;
    }
    return 0;
}