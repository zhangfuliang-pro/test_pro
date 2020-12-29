#include <common.h>
#include <command.h>
#include <malloc.h>
#include "asm/arch/mach/ms_types.h"
#include "asm/arch/mach/platform.h"
#include "asm/arch/mach/io.h"

#include <../drivers/mstar/aesdma/drvAESDMA.h>
#include <rtk.h>

extern void halt(void);

int do_sig_auth(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u32 image_start = 0;
    u32 image_size = 0;

    if (argc < 2)
	{
		printf("missing parameters\n");
		return CMD_RET_USAGE;
	}

    image_start = (u32)simple_strtoul(argv[1], NULL, 16);

    if (RTK_MAKER == image_get_rtk_maker(image_start))
    {
        image_size = image_get_rtk_size(image_start);

        if (runAuthenticate(image_start, image_size, 0))
        {
            printf("[U-Boot] Authenticate pass!\n\r");
        }
        else
        {
            printf("[U-Boot] Authenticate failed!\n\r");
			halt();
        }

        return 0;
    }

    return CMD_RET_USAGE;
}

U_BOOT_CMD(
	sigauth, CONFIG_SYS_MAXARGS, 1,	do_sig_auth,
	"Only verify digital signature without aes",
	"\n"
);

