#pragma once

#include "alli_common.h"
#include "alli_types.h"

typedef struct _LIBSSH2_CHANNEL LIBSSH2_CHANNEL;

namespace ALLIVaultCore
{
	namespace Helpers
	{
class pf_payload
{
public:
	ALLIVAULTCOREP_API pf_payload(void);
	ALLIVAULTCOREP_API pf_payload(SOCKET S, const char *dhost, unsigned int dport, const char *shost, unsigned int sport, LIBSSH2_CHANNEL *pf_channel,
		int c, bool *es);
	ALLIVAULTCOREP_API ~pf_payload(void);
	ALLIVAULTCOREP_API SOCKET get_forwardsock();
	ALLIVAULTCOREP_API const char *get_desthost();
	ALLIVAULTCOREP_API unsigned int get_destport();
	ALLIVAULTCOREP_API const char *get_shost();
	ALLIVAULTCOREP_API unsigned int get_sport();
	ALLIVAULTCOREP_API LIBSSH2_CHANNEL *get_ssh2_channel();
	ALLIVAULTCOREP_API int get_counter();
	ALLIVAULTCOREP_API bool *get_exitSignal();

private:
	SOCKET forwardsock;
	const char *remote_desthost;
	unsigned int remote_destport;
	const char *shost;
	unsigned int sport;
	LIBSSH2_CHANNEL *pf_channel_counter;
	int counter;
	bool *exitSignal;
};
	}
}
