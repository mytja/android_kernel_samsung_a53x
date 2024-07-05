/* SPDX-License-Identifier: GPL-2.0-only */
/*
* Samsung debugging features for Samsung's SoC's.
*
* Copyright (c) 2019 Samsung Electronics Co., Ltd.
*      http://www.samsung.com
*/

#ifndef SEC_DEBUG_H
#define SEC_DEBUG_H

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/sec_debug_types.h>
/*
 * Don't include additional headers. They can cause ABI violation problem
 * because this file is included many built-in drivers.
 */

struct task_struct;
struct irq_desc;
struct pt_regs;
struct freq_log;

/*
 * SEC DEBUG LAST KMSG
 */
#ifdef CONFIG_SEC_DEBUG
#define SEC_LKMSG_MAGICKEY 0x0000000a6c6c7546

extern void secdbg_lkmg_store(unsigned char *head_ptr,
		unsigned char *curr_ptr, size_t buf_size);
#else
#define secdbg_lkmg_store(a, b, c)		do {} while(0)
#endif

/*
 * SEC DEBUG MODE
 */
#if IS_ENABLED(CONFIG_SEC_DEBUG_MODE)
extern int secdbg_mode_check_sj(void);
extern int secdbg_mode_enter_upload(void);
#else
static inline int secdbg_mode_check_sj(void)
{
	return 0;
}
static inline int secdbg_mode_enter_upload(void)
{
	return 0;
}
#endif

/*
 * SEC DEBUG - DEBUG SNAPSHOT BASE HOOKING
 */
enum {
	DSS_KEVENT_TASK,
	DSS_KEVENT_WORK,
	DSS_KEVENT_IRQ,
	DSS_KEVENT_FREQ,
	DSS_KEVENT_IDLE,
	DSS_KEVENT_THRM,
	DSS_KEVENT_ACPM,
	DSS_KEVENT_MFRQ,
};

#define SD_ESSINFO_KEY_SIZE	(32)

struct ess_info_offset {
	char key[SD_ESSINFO_KEY_SIZE];
	unsigned long base;
	unsigned long last;
	unsigned int nr;
	unsigned int size;
	unsigned int per_core;
};

/*
 * SEC DEBUG AUTO COMMENT
 */
#ifdef CONFIG_SEC_DEBUG_AUTO_COMMENT
extern void secdbg_comm_log_disable(int type);
extern void secdbg_comm_log_once(int type);
#define DEFINE_STATIC_PR_AUTO_NAME_ONCE(name, lvl)			\
	static atomic_t ___pr_auto_counter_##name = ATOMIC_INIT(-1);	\
	static const char *___pr_auto_level_##name = (lvl)

#define pr_auto_name_once(name)					\
({								\
	if (atomic_read(&___pr_auto_counter_##name) <= 0)	\
		atomic_inc(&___pr_auto_counter_##name);		\
})

#define pr_auto_name(name, fmt, ...)				\
({								\
	if (atomic_read(&___pr_auto_counter_##name) > 0)	\
		pr_emerg(fmt, ##__VA_ARGS__);			\
	else							\
		printk(KERN_AUTO "%s" pr_fmt(fmt),		\
				___pr_auto_level_##name, ##__VA_ARGS__);	\
})

#define pr_auto_name_disable(name)				\
({								\
	atomic_set(&___pr_auto_counter_##name, 1);		\
})

#define pr_auto_name_on(__pr_auto_cond, name, fmt, ...)	\
({								\
	if (__pr_auto_cond)					\
		pr_auto_name(name, fmt, ##__VA_ARGS__);	\
	else							\
		pr_emerg(fmt, ##__VA_ARGS__);			\
})

#define pr_auto_on(__pr_auto_cond, lvl, fmt, ...)	\
({							\
	if (__pr_auto_cond)				\
		pr_auto(lvl, fmt, ##__VA_ARGS__);	\
	else						\
		pr_emerg(fmt, ##__VA_ARGS__);		\
})
#else
#define DEFINE_STATIC_PR_AUTO_NAME_ONCE(name, lvl)
#define pr_auto_name_once(name)
#define pr_auto_name(name, fmt, ...)	pr_emerg(fmt, ##__VA_ARGS__)
#define pr_auto_name_disable(name)
#define pr_auto_name_on(__pr_auto_cond, name, fmt, ...)		pr_emerg(fmt, ##__VA_ARGS__)
#define pr_auto_on(__pr_auto_cond, lvl, fmt, ...)		pr_emerg(fmt, ##__VA_ARGS__)
#endif /* CONFIG_SEC_DEBUG_AUTO_COMMENT */

/*
 * SEC DEBUG EXTRA INFO
 */
#if IS_ENABLED(CONFIG_SEC_DEBUG_EXTRA_INFO)
enum secdbg_exin_fault_type {
	UNDEF_FAULT,
	BAD_MODE_FAULT,
	WATCHDOG_FAULT,
	KERNEL_FAULT,
	MEM_ABORT_FAULT,
	SP_PC_ABORT_FAULT,
	PAGE_FAULT,
	ACCESS_USER_FAULT,
	EXE_USER_FAULT,
	ACCESS_USER_OUTSIDE_FAULT,
	BUG_FAULT,
	SERROR_FAULT,
	SEABORT_FAULT,
	PTRAUTH_FAULT,
	FAULT_MAX,
};

extern void secdbg_exin_set_finish(void);
extern void secdbg_exin_set_panic(const char *str);
extern void secdbg_exin_set_busmon(const char *str);
extern void secdbg_exin_set_sysmmu(const char *str);
extern void secdbg_exin_set_smpl(unsigned long count);
extern void secdbg_exin_set_decon(const char *str);
extern void secdbg_exin_set_batt(int cap, int volt, int temp, int curr);
extern void secdbg_exin_set_mfc_error(const char *str);
extern void secdbg_exin_set_aud(const char *str);
extern void secdbg_exin_set_gpuinfo(const char *str);
extern void secdbg_exin_set_epd(const char *str);
extern void secdbg_exin_set_asv(int bg, int mg, int lg, int g3dg, int mifg);
extern void secdbg_exin_set_ids(int bids, int mids, int lids, int gids);
extern void secdbg_exin_set_unfz(const char *comm, int pid);
extern char *secdbg_exin_get_unfz(void);
extern void secdbg_exin_set_hardlockup_type(const char *fmt, ...);
extern void secdbg_exin_set_hardlockup_data(const char *str);
extern void secdbg_exin_set_hardlockup_freq(const char *domain, struct freq_log *freq);
extern void secdbg_exin_set_hardlockup_ehld(unsigned int hl_info, unsigned int cpu);
extern void secdbg_exin_set_ufs(const char *str);
#else /* !CONFIG_SEC_DEBUG_EXTRA_INFO */
#define secdbg_exin_set_finish(a)	do { } while (0)
#define secdbg_exin_set_panic(a)	do { } while (0)
#define secdbg_exin_set_busmon(a)	do { } while (0)
#define secdbg_exin_set_sysmmu(a)	do { } while (0)
#define secdbg_exin_set_smpl(a)		do { } while (0)
#define secdbg_exin_set_decon(a)	do { } while (0)
#define secdbg_exin_set_batt(a, b, c, d)	do { } while (0)
#define secdbg_exin_set_mfc_error(a)	do { } while (0)
#define secdbg_exin_set_aud(a)		do { } while (0)
#define secdbg_exin_set_gpuinfo(a)		do { } while (0)
#define secdbg_exin_set_epd(a)		do { } while (0)
#define secdbg_exin_set_asv(a)		do { } while (0)
#define secdbg_exin_set_ids(a)		do { } while (0)
#define secdbg_exin_set_unfz(a)		do { } while (0)
#define secdbg_exin_get_unfz()		(NULL)
#define secdbg_exin_set_hardlockup_type(a, ...)	do { } while (0)
#define secdbg_exin_set_hardlockup_data(a)	do { } while (0)
#define secdbg_exin_set_hardlockup_freq(a, b)	do { } while (0)
#define secdbg_exin_set_hardlockup_ehld(a, b)	do { } while (0)
#define secdbg_exin_set_ufs(a)		do { } while (0)
#endif /* CONFIG_SEC_DEBUG_EXTRA_INFO */

#if IS_ENABLED(CONFIG_SEC_DEBUG_WATCHDOGD_FOOTPRINT)
extern void secdbg_wdd_set_keepalive(void);
extern void secdbg_wdd_set_start(void);
extern void secdbg_base_built_wdd_set_emerg_addr(unsigned long addr);
#else
#define secdbg_wdd_set_keepalive(a)	do { } while (0)
#define secdbg_wdd_set_start(a)		do { } while (0)
#define secdbg_base_built_wdd_set_emerg_addr(a)	do { } while (0)
#endif

#ifdef CONFIG_SEC_DEBUG_FREQ
extern void secdbg_freq_check(int type, unsigned long index, unsigned long freq);
#endif

#ifdef CONFIG_SEC_DEBUG_SYSRQ_KMSG
extern size_t secdbg_hook_get_curr_init_ptr(void);
extern size_t dbg_snapshot_get_curr_ptr_for_sysrq(void);
#endif

/* unfrozen task */
#if IS_ENABLED(CONFIG_SEC_DEBUG_UNFROZEN_TASK)
void secdbg_base_built_set_unfrozen_task(struct task_struct *task, uint64_t count);
#else
static inline void secdbg_base_built_set_unfrozen_task(struct task_struct *task, uint64_t count) {}
#endif /* CONFIG_SEC_DEBUG_UNFROZEN_TASK */

/* CONFIG_SEC_DEBUG_BAD_STACK_INFO */
extern void secdbg_base_set_bs_info_phase(int phase);

#if IS_ENABLED(CONFIG_SEC_DEBUG_DTASK)
static inline void secdbg_dtsk_built_set_data(long type, void *data)
{
	current->android_oem_data1[0] = (u64)type;
	current->android_oem_data1[1] = (u64)data;
}
static inline void secdbg_dtsk_built_clear_data(void)
{
	secdbg_dtsk_built_set_data(DTYPE_NONE, NULL);
}
#else
#define secdbg_dtsk_built_set_data(a, b)	do { } while (0)
#define secdbg_dtsk_built_clear_data()		do { } while (0)
#endif /* CONFIG_SEC_DEBUG_DTASK */

#if IS_ENABLED(CONFIG_SEC_DEBUG_PM_DEVICE_INFO)
extern void secdbg_base_built_set_device_shutdown_timeinfo(uint64_t start, uint64_t end, uint64_t duration, uint64_t func);
extern void secdbg_base_built_clr_device_shutdown_timeinfo(void);
extern void secdbg_base_built_set_shutdown_device(const char *fname, const char *dname);
extern void secdbg_base_built_set_suspend_device(const char *fname, const char *dname);
#else
#define secdbg_base_built_set_device_shutdown_timeinfo(a, b, c, d)	do { } while (0)
#define secdbg_base_built_clr_device_shutdown_timeinfo()	do { } while (0)
#define secdbg_base_built_set_shutdown_device(a, b)		do { } while (0)
#define secdbg_base_built_set_suspend_device(a, b)		do { } while (0)
#endif /* CONFIG_SEC_DEBUG_PM_DEVICE_INFO */

#if IS_ENABLED(CONFIG_SEC_DEBUG_TASK_IN_STATE_INFO)
void secdbg_base_built_set_task_in_pm_suspend(struct task_struct *task);
void secdbg_base_built_set_task_in_sync_irq(struct task_struct *task, unsigned int irq, struct irq_desc *desc);
#else
#define secdbg_base_built_set_task_in_pm_suspend(a)		do { } while (0)
#define secdbg_base_built_set_task_in_sync_irq(a, b, c)		do { } while (0)
#endif /* CONFIG_SEC_DEBUG_PM_DEVICE_INFO */

#if IS_ENABLED(CONFIG_SEC_DEBUG_SOFTDOG)
void secdbg_softdog_show_info(void);
#else
#define secdbg_softdog_show_info()		do { } while (0)
#endif

#if IS_ENABLED(CONFIG_SEC_DEBUG_HANDLE_BAD_STACK)
extern void secdbg_base_built_check_handle_bad_stack(void);
#else
static inline void secdbg_base_built_check_handle_bad_stack(void) { }
#endif

#ifdef CONFIG_SEC_DEBUG_MEMTAB
#define SDBG_KNAME_LEN	64

struct secdbg_member_type {
	char member[SDBG_KNAME_LEN];
	uint16_t size;
	uint16_t offset;
	uint16_t unused[2];
};

#define SECDBG_DEFINE_MEMBER_TYPE(key, st, mem)					\
	const struct secdbg_member_type sdbg_##key				\
		__attribute__((__section__(".secdbg_mbtab." #key))) = {		\
		.member = #key,							\
		.size = sizeof_field(struct st, mem),				\
		.offset = offsetof(struct st, mem),				\
	}
#else
#define SECDBG_DEFINE_MEMBER_TYPE(a, b, c)
#endif /* CONFIG_SEC_DEBUG_MEMTAB */

extern struct atomic_notifier_head sec_power_off_notifier_list;

extern void secdbg_exin_set_main_ocp(void *main_ocp_cnt, void *main_oi_cnt, int buck_cnt);

#endif /* SEC_DEBUG_H */

