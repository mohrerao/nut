#include "main.h"
#include "nutdrv_qx.h"
#include "nutdrv_qx_blazer-common.h"

#define QPSIPLUS_VERSION "QPSI_PLUS 0.01"

/* Composite lookup table */
static item_t qpsi_qx2nut[] = {
    /* QPSI: power metrics */
    { "input.voltage", 0, NULL, "QGS\r", "", 0, '(', "", 0, 0, "%.1f", QX_FLAG_QUICK_POLL, NULL, NULL, NULL },
    { "output.voltage", 0, NULL, "QGS\r", "", 0, '(', "", 2, 2, "%.1f", QX_FLAG_QUICK_POLL, NULL, NULL, NULL },
    { "input.frequency", 0, NULL, "QGS\r", "", 0, '(', "", 3, 3, "%.1f", QX_FLAG_QUICK_POLL, NULL, NULL, NULL },
    { "ups.load", 0, NULL, "QGS\r", "", 0, '(', "", 13, 13, "%.0f", QX_FLAG_QUICK_POLL, NULL, NULL, NULL },
    { "battery.voltage", 0, NULL, "QGS\r", "", 0, '(', "", 4, 4, "%.1f", QX_FLAG_QUICK_POLL, NULL, NULL, NULL },
    { "ups.status", 0, NULL, "QGS\r", "", 0, '(', "", 14, 14, NULL, QX_FLAG_QUICK_POLL, NULL, NULL, blazer_process_status_bits },

    /* QGS: device summary */
    { "ups.voltage.nominal", 0, NULL, "QPSI\r", "", 0, '(', "", 2, 2, "%.1f", 0, NULL, NULL, NULL },
    { "ups.voltage.min", 0, NULL, "QPSI\r", "", 0, '(', "", 4, 4, "%.1f", 0, NULL, NULL, NULL },

    /* QGS2: rating info */
    { "ups.runtime.charging", 0, NULL, "QGS2\r", "", 0, '(', "", 1, 1, "%.0f", QX_FLAG_STATIC, NULL, NULL, NULL },

    { NULL, 0, NULL, NULL, "", 0, 0, "", 0, 0, NULL, 0, NULL, NULL, NULL }
};




static void qpsi_initups(void) {
    blazer_initups_light(qpsi_qx2nut);
}

subdriver_t qpsi_plus_subdriver = {
    .name = QPSIPLUS_VERSION,
    .claim = blazer_claim_light,
    .qx2nut = qpsi_qx2nut,
    .initups = qpsi_initups,
    .initinfo = NULL,
    .makevartable = blazer_makevartable_light,
    .accepted = "QPSI",
    .rejected = NULL
#ifdef TESTING
    , .testing = NULL
#endif
};
