#pragma once

#include <simple_wgsl.h>

void check_if_error(SwResult result, char *errors);

void check_if_diagnostic_error(WgslDiagnosticList *list);