#include <stdint.h>
#include <stddef.h>

#define REG8(a)   (*(volatile uint8_t  *)(a))
#define REG16(a)  (*(volatile uint16_t *)(a))
#define REG32(a)  (*(volatile uint32_t *)(a))

#define NVMCTRL_CTRLB       REG32(0x41004004u)

#define PM_AHBMASK          REG32(0x40000414u)
#define PM_APBBMASK         REG32(0x4000041Cu)
#define PM_AHBMASK_USB      (1u << 6)
#define PM_APBBMASK_USB     (1u << 5)

#define SYSCTRL_INTFLAG     REG32(0x4000080Cu)
#define SYSCTRL_DFLLCTRL    REG16(0x40000824u)
#define SYSCTRL_DFLLVAL     REG32(0x40000828u)
#define SYSCTRL_DFLLMUL     REG32(0x4000082Cu)
#define SYSCTRL_INTFLAG_DFLLRDY (1u << 4)
#define DFLLCTRL_ENABLE     (1u << 1)
#define DFLLCTRL_MODE       (1u << 2)
#define DFLLCTRL_USBCRM     (1u << 5)
#define DFLLCTRL_CCDIS      (1u << 8)

#define GCLK_CTRL           REG8 (0x40000C00u)
#define GCLK_STATUS         REG8 (0x40000C01u)
#define GCLK_CLKCTRL        REG16(0x40000C02u)
#define GCLK_GENCTRL        REG32(0x40000C04u)
#define GCLK_GENDIV         REG32(0x40000C08u)
#define GCLK_STATUS_SYNCBUSY (1u << 7)
#define GCLK_SRC_DFLL48M    7u
#define GCLK_ID_USB         0x06u

#define PORT_PINCFG(n)      REG8(0x41004440u + (n))
#define PORT_PMUX(n)        REG8(0x41004430u + (n))
#define PINCFG_PMUXEN       (1u << 0)
#define PMUX_FUNC_G         6u

#define USB_BASE           0x41005000u
#define USB_CTRLA          REG8 (USB_BASE + 0x00u)
#define USB_SYNCBUSY       REG8 (USB_BASE + 0x02u)
#define USB_QOSCTRL        REG8 (USB_BASE + 0x03u)
#define USB_CTRLB          REG16(USB_BASE + 0x08u)
#define USB_DADD           REG8 (USB_BASE + 0x0Au)
#define USB_INTFLAG        REG16(USB_BASE + 0x1Cu)
#define USB_DESCADD        REG32(USB_BASE + 0x24u)
#define USB_PADCAL         REG16(USB_BASE + 0x28u)

#define USB_CTRLA_SWRST    (1u << 0)
#define USB_CTRLA_ENABLE   (1u << 1)
#define USB_CTRLA_RUNSTDBY (1u << 2)
#define USB_CTRLA_MODE_DEV (0u << 7)
#define USB_SYNCBUSY_SWRST (1u << 0)
#define USB_SYNCBUSY_ENABLE (1u << 1)
#define USB_CTRLB_DETACH   (1u << 0)
#define USB_INTFLAG_EORST  (1u << 3)

#define USB_EP(n)          (USB_BASE + 0x100u + (n) * 0x20u)
#define USB_EPCFG(n)       REG8(USB_EP(n) + 0x00u)
#define USB_EPSTATUSCLR(n) REG8(USB_EP(n) + 0x04u)
#define USB_EPSTATUSSET(n) REG8(USB_EP(n) + 0x05u)
#define USB_EPSTATUS(n)    REG8(USB_EP(n) + 0x06u)
#define USB_EPINTFLAG(n)   REG8(USB_EP(n) + 0x07u)

#define EPCFG_TYPE0(v)     ((v) << 0)
#define EPCFG_TYPE1(v)     ((v) << 4)
#define EPTYPE_CONTROL     1u
#define EPTYPE_INT_IN      4u

#define EPINT_TRCPT0       (1u << 0)
#define EPINT_TRCPT1       (1u << 1)
#define EPINT_RXSTP        (1u << 4)
#define EPSTATUS_DTGLIN    (1u << 1)
#define EPSTATUS_STALLRQ0  (1u << 4)
#define EPSTATUS_STALLRQ1  (1u << 5)
#define EPSTATUS_BK0RDY    (1u << 6)
#define EPSTATUS_BK1RDY    (1u << 7)

#define PCKSIZE_SIZE_8     (0u << 28)
#define PCKSIZE_SIZE_64    (3u << 28)
#define PCKSIZE_IN(len)    ((uint32_t)(len) & 0x3FFFu)
#define PCKSIZE_OUT(cap)   ((uint32_t)(cap) << 14)

#define SYST_CSR           REG32(0xE000E010u)
#define SYST_RVR           REG32(0xE000E014u)
#define SYST_CVR           REG32(0xE000E018u)
#define SYST_CSR_ENABLE    (1u << 0)
#define SYST_CSR_CLKCORE   (1u << 2)
#define SYST_CSR_COUNTFLAG (1u << 16)

#define NVM_CAL_WORD1      REG32(0x00806024u)

void *memset(void *d, int c, size_t n)
{
	uint8_t *p = d;
	while (n--)
		*p++ = (uint8_t)c;
	return d;
}

void *memcpy(void *d, const void *s, size_t n)
{
	uint8_t *a = d;
	const uint8_t *b = s;
	while (n--)
		*a++ = *b++;
	return d;
}

#define VID  0x1209
#define PID  0x0001

static const uint8_t dev_desc[18] = {
	18, 0x01,
	0x00, 0x02,
	0x00, 0x00, 0x00,
	64,
	(VID & 0xFF), (VID >> 8),
	(PID & 0xFF), (PID >> 8),
	0x00, 0x01,
	1, 2, 0,
	1,
};

#define REPORT_DESC_LEN 63
static const uint8_t report_desc[REPORT_DESC_LEN] = {
	0x05, 0x01,
	0x09, 0x06,
	0xA1, 0x01,
	0x05, 0x07,
	0x19, 0xE0,
	0x29, 0xE7,
	0x15, 0x00,
	0x25, 0x01,
	0x75, 0x01,
	0x95, 0x08,
	0x81, 0x02,
	0x95, 0x01,
	0x75, 0x08,
	0x81, 0x03,
	0x95, 0x05,
	0x75, 0x01,
	0x05, 0x08,
	0x19, 0x01,
	0x29, 0x05,
	0x91, 0x02,
	0x95, 0x01,
	0x75, 0x03,
	0x91, 0x03,
	0x95, 0x06,
	0x75, 0x08,
	0x15, 0x00,
	0x25, 0x65,
	0x05, 0x07,
	0x19, 0x00,
	0x29, 0x65,
	0x81, 0x00,
	0xC0,
};

#define CFG_DESC_LEN 34
static const uint8_t cfg_desc[CFG_DESC_LEN] = {
	9, 0x02, CFG_DESC_LEN, 0x00, 1, 1, 0, 0x80, 50,
	9, 0x04, 0, 0, 1, 0x03, 0x01, 0x01, 0,
	9, 0x21, 0x11, 0x01, 0x00, 1, 0x22, REPORT_DESC_LEN, 0x00,
	7, 0x05, 0x81, 0x03, 8, 0x00, 5,
};

typedef struct {
	uint32_t ADDR;
	uint32_t PCKSIZE;
	uint16_t EXTREG;
	uint8_t  STATUS_BK;
	uint8_t  _pad0;
	uint32_t _pad1;
} usb_bank_t;

typedef struct { usb_bank_t bank[2]; } usb_ep_t;

typedef struct {
	uint8_t  bmRequestType;
	uint8_t  bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} setup_t;

static volatile usb_ep_t ep_desc[2] __attribute__((aligned(4)));
static uint8_t ep0_out[64] __attribute__((aligned(4)));
static uint8_t ep0_in[64]  __attribute__((aligned(4)));
static uint8_t ep1_in[8]   __attribute__((aligned(4)));
static setup_t setup;
static volatile uint8_t usb_config_value;
static volatile uint8_t usb_configured;

static void clock_init(void)
{
	NVMCTRL_CTRLB = (NVMCTRL_CTRLB & ~(0xFu << 1)) | (1u << 1);

	PM_AHBMASK  |= PM_AHBMASK_USB;
	PM_APBBMASK |= PM_APBBMASK_USB;

	SYSCTRL_DFLLCTRL = DFLLCTRL_ENABLE;
	while (!(SYSCTRL_INTFLAG & SYSCTRL_INTFLAG_DFLLRDY))
		;

	SYSCTRL_DFLLVAL = ((NVM_CAL_WORD1 >> 26) & 0x3Fu) << 10;

	SYSCTRL_DFLLMUL = (6u << 26) | (0x3Fu << 16) | 48000u;

	SYSCTRL_DFLLCTRL = DFLLCTRL_ENABLE | DFLLCTRL_MODE |
	                   DFLLCTRL_USBCRM | DFLLCTRL_CCDIS;
	while (!(SYSCTRL_INTFLAG & SYSCTRL_INTFLAG_DFLLRDY))
		;

	GCLK_GENDIV = 0u;
	while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY)
		;
	GCLK_GENCTRL = 0u | (GCLK_SRC_DFLL48M << 8) | (1u << 16) | (1u << 17);
	while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY)
		;

	GCLK_CLKCTRL = GCLK_ID_USB | (0u << 8) | (1u << 14);
	while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY)
		;
}

static void usb_task(void);

static void systick_init(void)
{
	SYST_RVR = 48000u - 1u;
	SYST_CVR = 0u;
	SYST_CSR = SYST_CSR_ENABLE | SYST_CSR_CLKCORE;
}

static void delay_ms(uint32_t ms)
{
	while (ms--) {
		while (!(SYST_CSR & SYST_CSR_COUNTFLAG))
			usb_task();
	}
}

static void ep0_init(void)
{
	USB_EPCFG(0) = EPCFG_TYPE0(EPTYPE_CONTROL) | EPCFG_TYPE1(EPTYPE_CONTROL);
	USB_EPINTFLAG(0) = 0xFF;

	ep_desc[0].bank[0].ADDR    = (uint32_t)ep0_out;
	ep_desc[0].bank[0].PCKSIZE = PCKSIZE_SIZE_64 | PCKSIZE_OUT(64);
	ep_desc[0].bank[1].ADDR    = (uint32_t)ep0_in;
	ep_desc[0].bank[1].PCKSIZE = PCKSIZE_SIZE_64;

	USB_EPSTATUSCLR(0) = EPSTATUS_BK0RDY;
	USB_EPSTATUSCLR(0) = EPSTATUS_BK1RDY;
}

static void ep1_init(void)
{
	USB_EPCFG(1) = EPCFG_TYPE1(EPTYPE_INT_IN);
	USB_EPINTFLAG(1) = 0xFF;
	USB_EPSTATUSCLR(1) = EPSTATUS_BK1RDY | EPSTATUS_DTGLIN |
	                     EPSTATUS_STALLRQ0 | EPSTATUS_STALLRQ1;
	ep_desc[1].bank[1].ADDR    = (uint32_t)ep1_in;
	ep_desc[1].bank[1].PCKSIZE = PCKSIZE_SIZE_8;
}

static void ctrl_stall(void)
{
	USB_EPSTATUSSET(0) = EPSTATUS_STALLRQ0 | EPSTATUS_STALLRQ1;
}

static void ctrl_send(const void *data, uint32_t len)
{
	if (len > setup.wLength)
		len = setup.wLength;
	memcpy(ep0_in, data, len);
	ep_desc[0].bank[1].PCKSIZE = PCKSIZE_SIZE_64 | PCKSIZE_IN(len);
	USB_EPINTFLAG(0) = EPINT_TRCPT1;
	USB_EPSTATUSSET(0) = EPSTATUS_BK1RDY;
}

static void ctrl_zlp(void)
{
	ep_desc[0].bank[1].PCKSIZE = PCKSIZE_SIZE_64 | PCKSIZE_IN(0);
	USB_EPINTFLAG(0) = EPINT_TRCPT1;
	USB_EPSTATUSSET(0) = EPSTATUS_BK1RDY;
}

static void send_string(uint8_t idx)
{
	uint8_t *b = ep0_in;

	if (idx == 0) {
		b[0] = 4; b[1] = 0x03; b[2] = 0x09; b[3] = 0x04;
		ctrl_send(b, 4);
		return;
	}

	const char *s;
	if (idx == 1)
		s = "ZeptoDuck";
	else if (idx == 2)
		s = "ZeptoDuck HID";
	else {
		ctrl_stall();
		return;
	}

	uint8_t n = 0;
	while (s[n])
		n++;
	b[0] = (uint8_t)(2 + n * 2);
	b[1] = 0x03;
	for (uint8_t i = 0; i < n; i++) {
		b[2 + i * 2] = (uint8_t)s[i];
		b[3 + i * 2] = 0;
	}
	ctrl_send(b, b[0]);
}

static void handle_setup(void)
{
	memcpy(&setup, ep0_out, sizeof(setup));
	USB_EPINTFLAG(0) = EPINT_RXSTP | EPINT_TRCPT0 | EPINT_TRCPT1;

	uint8_t kind = setup.bmRequestType & 0x60u;

	if (kind == 0x00) {
		switch (setup.bRequest) {
		case 0x06: {
			uint8_t t = setup.wValue >> 8;
			uint8_t i = setup.wValue & 0xFF;
			if (t == 0x01)
				ctrl_send(dev_desc, sizeof dev_desc);
			else if (t == 0x02)
				ctrl_send(cfg_desc, sizeof cfg_desc);
			else if (t == 0x03)
				send_string(i);
			else if (t == 0x22)
				ctrl_send(report_desc, sizeof report_desc);
			else
				ctrl_stall();
			break;
		}
		case 0x05:
			ctrl_zlp();
			USB_DADD = (1u << 7) | (setup.wValue & 0x7Fu);
			break;
		case 0x09:
			usb_config_value = setup.wValue & 0xFF;
			if (usb_config_value)
				ep1_init();
			usb_configured = usb_config_value ? 1 : 0;
			ctrl_zlp();
			break;
		case 0x08:
			ep0_in[0] = usb_config_value;
			ctrl_send(ep0_in, 1);
			break;
		case 0x00:
			ep0_in[0] = 0; ep0_in[1] = 0;
			ctrl_send(ep0_in, 2);
			break;
		case 0x0A:
		case 0x01:
		case 0x03:
			ctrl_zlp();
			break;
		case 0x0B:
			ep0_in[0] = 0;
			ctrl_send(ep0_in, 1);
			break;
		default:
			ctrl_stall();
		}
	} else if (kind == 0x20) {
		switch (setup.bRequest) {
		case 0x01:
			memset(ep0_in, 0, 8);
			ctrl_send(ep0_in, 8);
			break;
		case 0x02:
			ep0_in[0] = 0;
			ctrl_send(ep0_in, 1);
			break;
		case 0x03:
			ep0_in[0] = 1;
			ctrl_send(ep0_in, 1);
			break;
		case 0x09:
		case 0x0A:
		case 0x0B:
			ctrl_zlp();
			break;
		default:
			ctrl_stall();
		}
	} else {
		ctrl_stall();
	}

	ep_desc[0].bank[0].PCKSIZE = PCKSIZE_SIZE_64 | PCKSIZE_OUT(64);
	ep_desc[0].bank[0].STATUS_BK = 0;
	USB_EPSTATUSCLR(0) = EPSTATUS_BK0RDY;
}

static void usb_task(void)
{
	if (USB_INTFLAG & USB_INTFLAG_EORST) {
		USB_INTFLAG = USB_INTFLAG_EORST;
		USB_DADD = 0;
		usb_configured = 0;
		usb_config_value = 0;
		ep0_init();
		return;
	}

	if (USB_EPINTFLAG(0) & EPINT_RXSTP)
		handle_setup();

	if (USB_EPINTFLAG(0) & EPINT_TRCPT0) {
		USB_EPINTFLAG(0) = EPINT_TRCPT0;
		USB_EPSTATUSCLR(0) = EPSTATUS_BK0RDY;
	}
}

static void usb_init(void)
{
	PORT_PINCFG(24) = PINCFG_PMUXEN;
	PORT_PINCFG(25) = PINCFG_PMUXEN;
	PORT_PMUX(12)   = (PMUX_FUNC_G << 0) | (PMUX_FUNC_G << 4);

	USB_CTRLA = USB_CTRLA_SWRST;
	while (USB_SYNCBUSY & USB_SYNCBUSY_SWRST)
		;
	while (USB_CTRLA & USB_CTRLA_SWRST)
		;

	uint32_t cal = NVM_CAL_WORD1;
	uint32_t transn = (cal >> 13) & 0x1Fu;
	uint32_t transp = (cal >> 18) & 0x1Fu;
	uint32_t trim   = (cal >> 23) & 0x07u;
	if (transn == 0x1Fu) transn = 5;
	if (transp == 0x1Fu) transp = 29;
	if (trim   == 0x07u) trim   = 3;
	USB_PADCAL = (uint16_t)(transp | (transn << 6) | (trim << 12));

	USB_QOSCTRL  = (3u << 0) | (3u << 2);
	USB_DESCADD  = (uint32_t)&ep_desc[0];
	USB_CTRLA    = USB_CTRLA_MODE_DEV | USB_CTRLA_RUNSTDBY;
	USB_CTRLB    = USB_CTRLB_DETACH;

	USB_CTRLA |= USB_CTRLA_ENABLE;
	while (USB_SYNCBUSY & USB_SYNCBUSY_ENABLE)
		;

	ep0_init();
	USB_CTRLB &= ~USB_CTRLB_DETACH;
}

#define MOD_LSHIFT 0x02
#define MOD_LGUI   0x08
#define KEY_ENTER  0x28

static void kbd_report(uint8_t mod, uint8_t key)
{
	ep1_in[0] = mod;
	ep1_in[1] = 0;
	ep1_in[2] = key;
	ep1_in[3] = ep1_in[4] = ep1_in[5] = ep1_in[6] = ep1_in[7] = 0;

	ep_desc[1].bank[1].PCKSIZE = PCKSIZE_SIZE_8 | PCKSIZE_IN(8);
	USB_EPINTFLAG(1) = EPINT_TRCPT1;
	USB_EPSTATUSSET(1) = EPSTATUS_BK1RDY;

	uint32_t guard = 2000000u;
	while (!(USB_EPINTFLAG(1) & EPINT_TRCPT1) && guard--)
		usb_task();
}

static uint8_t ascii_to_key(char c, uint8_t *mod)
{
	*mod = 0;
	if (c >= 'a' && c <= 'z')
		return (uint8_t)(0x04 + (c - 'a'));
	if (c >= 'A' && c <= 'Z') {
		*mod = MOD_LSHIFT;
		return (uint8_t)(0x04 + (c - 'A'));
	}
	if (c >= '1' && c <= '9')
		return (uint8_t)(0x1E + (c - '1'));

	switch (c) {
	case '0': return 0x27;
	case '\n': case '\r': return KEY_ENTER;
	case '\t': return 0x2B;
	case ' ': return 0x2C;
	case '-': return 0x2D;
	case '=': return 0x2E;
	case '[': return 0x2F;
	case ']': return 0x30;
	case '\\': return 0x31;
	case ';': return 0x33;
	case '\'': return 0x34;
	case '`': return 0x35;
	case ',': return 0x36;
	case '.': return 0x37;
	case '/': return 0x38;
	case '!': *mod = MOD_LSHIFT; return 0x1E;
	case '@': *mod = MOD_LSHIFT; return 0x1F;
	case '#': *mod = MOD_LSHIFT; return 0x20;
	case '$': *mod = MOD_LSHIFT; return 0x21;
	case '%': *mod = MOD_LSHIFT; return 0x22;
	case '^': *mod = MOD_LSHIFT; return 0x23;
	case '&': *mod = MOD_LSHIFT; return 0x24;
	case '*': *mod = MOD_LSHIFT; return 0x25;
	case '(': *mod = MOD_LSHIFT; return 0x26;
	case ')': *mod = MOD_LSHIFT; return 0x27;
	case '_': *mod = MOD_LSHIFT; return 0x2D;
	case '+': *mod = MOD_LSHIFT; return 0x2E;
	case '{': *mod = MOD_LSHIFT; return 0x2F;
	case '}': *mod = MOD_LSHIFT; return 0x30;
	case '|': *mod = MOD_LSHIFT; return 0x31;
	case ':': *mod = MOD_LSHIFT; return 0x33;
	case '"': *mod = MOD_LSHIFT; return 0x34;
	case '~': *mod = MOD_LSHIFT; return 0x35;
	case '<': *mod = MOD_LSHIFT; return 0x36;
	case '>': *mod = MOD_LSHIFT; return 0x37;
	case '?': *mod = MOD_LSHIFT; return 0x38;
	}
	return 0;
}

static void type_str(const char *s)
{
	for (; *s; s++) {
		uint8_t mod, key = ascii_to_key(*s, &mod);
		if (!key)
			continue;
		kbd_report(mod, key);
		kbd_report(0, 0);
	}
}

static void run_payload(void)
{
	delay_ms(2000);

	kbd_report(MOD_LGUI, 0x15);
	kbd_report(0, 0);
	delay_ms(600);

	type_str("notepad\n");
	delay_ms(1200);

	type_str("Hello from ZeptoDuck - the world's smallest USB Rubber Ducky!\n");
}

int main(void)
{
	clock_init();
	systick_init();
	usb_init();

	while (!usb_configured)
		usb_task();

	run_payload();

	for (;;)
		usb_task();
}

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;

void Reset_Handler(void)
{
	uint32_t *src = &_sidata;
	uint32_t *dst = &_sdata;
	while (dst < &_edata)
		*dst++ = *src++;
	for (dst = &_sbss; dst < &_ebss; )
		*dst++ = 0;

	main();
	for (;;)
		;
}

void Default_Handler(void)
{
	for (;;)
		;
}

#define ALIAS __attribute__((weak, alias("Default_Handler")))
void NMI_Handler(void)        ALIAS;
void HardFault_Handler(void)  ALIAS;
void SVC_Handler(void)        ALIAS;
void PendSV_Handler(void)     ALIAS;
void SysTick_Handler(void)    ALIAS;

__attribute__((section(".vectors"), used))
void (*const vector_table[])(void) = {
	(void (*)(void))&_estack,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	0, 0, 0, 0, 0, 0, 0,
	SVC_Handler,
	0, 0,
	PendSV_Handler,
	SysTick_Handler,
	Default_Handler, Default_Handler, Default_Handler, Default_Handler,
	Default_Handler, Default_Handler, Default_Handler, Default_Handler,
	Default_Handler, Default_Handler, Default_Handler, Default_Handler,
	Default_Handler, Default_Handler, Default_Handler, Default_Handler,
	Default_Handler, Default_Handler,
};
