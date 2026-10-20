
#include <stdio.h>

#include <simple_wgsl.h>

#include "error.h"
#include "common.h"

// Heavy-handed approach to error handling
void check_if_error(SwResult result, char *errors) {
#ifdef DEBUG
    if (result != SW_OK) {
        if (errors == NULL) {
            fprintf(stderr, "Error Unknown");
        } else {
            fprintf(stderr, "Error: %s\n", errors);
        }
        exit(EXIT_FAILURE);
    }
#endif
}

void check_if_diagnostic_error(WgslDiagnosticList *list) {
#ifdef DEBUG
    if (list != NULL) {
        for (int i = 0; i < list->count; i++) {
            WgslDiagnosticSeverity severity = list->items[i].severity;
            if (severity == WGSL_DIAG_ERROR || severity == WGSL_DIAG_WARNING) {
                fprintf(stderr, "Error: %s\n", list->items[i].message);
            }
        }
        exit(EXIT_FAILURE);
    }
#endif
}