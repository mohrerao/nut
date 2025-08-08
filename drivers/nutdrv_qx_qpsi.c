/*
 * nutdrv_qx_qpsi.c - Subdriver for QPSI+ protocol based UPSes
 *
 * Based on nutdrv_qx_q1.c by Daniele Pezzini <hyouko@gmail.com>
 * Modified for QGS query format by ChatGPT <https://openai.com>
 */

#include "main.h"
#include "nutdrv_qx.h"
#include "nutdrv_qx_blazer-common.h"

#define QPSI_VERSION "QPSI 0.01"

/* Lookup table for QGS response:
   Example response: 
   (222.0 49.1 230.1 50.0 000.7 005 371.0 ----- 053.2 ----- 038.0 ------------
*/

static item_t qpsi_qx2nut[] = {
    { "ups.realpower", 0, NULL, "QGS2\r", "", 55, '(', "", 8, 13, "%.0f", 0, NULL, NULL, NULL },
    { "input.voltage",     0, NULL, "QGS\r", "", 63, '(', "",  1,  6, "%.1f", 0, NULL, NULL, NULL },
    { "input.frequency",   0, NULL, "QGS\r", "", 63, '(', "",  7, 12, "%.1f", 0, NULL, NULL, NULL },
    { "output.voltage",    0, NULL, "QGS\r", "", 63, '(', "", 12, 17, "%.1f", 0, NULL, NULL, NULL },
    { "output.frequency",  0, NULL, "QGS\r", "", 63, '(', "", 18, 24, "%.1f", 0, NULL, NULL, NULL },
    { "output.load",  0, NULL, "QGS\r", "", 63, '(', "", 31, 37, "%.1f", 0, NULL, NULL, NULL },
    { "battery.voltage",   0, NULL, "QGS\r", "", 63, '(', "", 45, 50, "%.1f", 0, NULL, NULL, NULL },
    { "ups.temperature", 0, NULL, "QGS\r", "", 63, '(', "", 58, 62, "%.1f", 0, NULL, NULL, NULL },
    { NULL, 0, NULL, NULL, "", 0, 0, "", 0, 0, NULL, 0, NULL, NULL, NULL }
};

#ifdef TESTING
static testing_t qpsi_testing[] = {
    { "QGS2\r", "(222.0 49.1 230.1 50.0 000.7 005 371.0 ----- 053.2 ----- 038.0 ------------\r", -1 },
    { NULL }
};
#endif

static void qpsi_initups(void)
{
    blazer_initups_light(qpsi_qx2nut);
}

subdriver_t qpsi_subdriver = {
    QPSI_VERSION,
    blazer_claim_light,
    qpsi_qx2nut,
    qpsi_initups,
    NULL,
    blazer_makevartable_light,
    "ACK",
    NULL,
#ifdef TESTING
    qpsi_testing,
#endif
};
