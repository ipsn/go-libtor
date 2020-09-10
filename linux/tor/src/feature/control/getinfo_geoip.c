
#include "core/or/or.h"
#include "core/mainloop/connection.h"
#include "feature/control/control.h"
#include "feature/control/getinfo_geoip.h"
#include "lib/geoip/geoip.h"

/** Helper used to implement GETINFO ip-to-country/... controller command. */
int
getinfo_helper_geoip(control_connection_t *control_conn,
                     const char *question, char **answer,
                     const char **errmsg)
{
  (void)control_conn;
  if (!strcmpstart(question, "ip-to-country/")) {
    int c;
    sa_family_t family;
    tor_addr_t addr;
    question += strlen("ip-to-country/");

    if (!strcmp(question, "ipv4-available") ||
        !strcmp(question, "ipv6-available")) {
      family = !strcmp(question, "ipv4-available") ? AF_INET : AF_INET6;
      const int available = geoip_is_loaded(family);
      tor_asprintf(answer, "%d", !! available);
      return 0;
    }

    family = tor_addr_parse(&addr, question);
    if (family != AF_INET && family != AF_INET6) {
      *errmsg = "Invalid address family";
      return -1;
    }
    if (!geoip_is_loaded(family)) {
      *errmsg = "GeoIP data not loaded";
      return -1;
    }
    if (family == AF_INET)
      c = geoip_get_country_by_ipv4(tor_addr_to_ipv4h(&addr));
    else                      /* AF_INET6 */
      c = geoip_get_country_by_ipv6(tor_addr_to_in6(&addr));
    *answer = tor_strdup(geoip_get_country_name(c));
  }
  return 0;
}
