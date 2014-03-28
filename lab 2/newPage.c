#include <stdio.h>

void newPage(int *pageCount, int *lineCount, double *pageGross, double *pageFICA, double *pageNet, FILE *outFile) {
    // Print footer for previous page and header for new page and all necessary totals
    char str1[15], str2[15], str3[15], str4[15];
    if (*pageGross >= 1000) {
        sprintf(str1, "$%d,%03d.%02.0f ", (int)*pageGross/1000, (int)*pageGross % 1000, (*pageGross-floor(*pageGross))*100);
    } else {
        sprintf(str1, "$%d.%02.0f ", (int)*pageGross % 1000, (*pageGross-floor(*pageGross))*100);
    }
    if (*pageFICA >= 1000) {
        sprintf(str2, "$%d,%03d.%02.0f ", (int)*pageFICA/1000, (int)*pageFICA % 1000, (*pageFICA-floor(*pageFICA))*100);
    } else {
        sprintf(str2, "$%d.%02.0f ", (int)*pageFICA % 1000, (*pageFICA-floor(*pageFICA))*100);
    }
    if (*pageNet >= 1000) {
        sprintf(str3, "$%d,%03d.%02.0f ", (int)*pageNet/1000, (int)*pageNet % 1000, (*pageNet-floor(*pageNet))*100);
    } else {
        sprintf(str3, "$%d.%02.0f ", (int)*pageNet % 1000, (*pageNet-floor(*pageNet))*100);
    }

    fprintf(outFile, "\nPage totals: %61s %11s %12s\n", str1, str2, str3);
    fprintf(outFile, "\n%92s %d\n\n\f", "Page", *pageCount);
    fprintf(outFile, "\n%20s\n", "ACME");
    fprintf(outFile, "%-4s %6s %17s %12s %14s %13s %11s %12s\n\n", "Emp #", "Given", "Surname", "Dept", "New YTD" , "Gross", "FICA", "Net");
    *pageCount += 1;
    *pageGross = *pageFICA = *pageNet = 0;
    *lineCount = 1;
}
