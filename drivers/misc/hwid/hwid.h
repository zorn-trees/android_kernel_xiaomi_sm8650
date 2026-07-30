/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020-2021 Xiaomi, Inc.
 * Copyright (C) 2022 The LineageOS Project
 */

#ifndef _XIAOMI_HWID_H_
#define _XIAOMI_HWID_H_

#include <linux/types.h>

#define HARDWARE_PROJECT_UNKNOWN	0
#define HARDWARE_PROJECT_N2		1
#define HARDWARE_PROJECT_N3		2
#define HARDWARE_PROJECT_N11U		3
#define HARDWARE_PROJECT_N1		4
#define HARDWARE_PROJECT_O16U		5
#define HARDWARE_PROJECT_N8		6
#define HARDWARE_PROJECT_N18		7
#define HARDWARE_PROJECT_N16T		8
#define HARDWARE_PROJECT_N9		9
#define HARDWARE_PROJECT_O81		10
#define HARDWARE_PROJECT_O82		11
#define HARDWARE_PROJECT_O11		13

enum xiaomi_country {
	XIAOMI_COUNTRY_CN	= 0x00,
	XIAOMI_COUNTRY_GLOBAL	= 0x01,
	XIAOMI_COUNTRY_INDIA	= 0x02,
	XIAOMI_COUNTRY_JAPAN	= 0x03,
	XIAOMI_COUNTRY_INVALID	= 0x04,
};

/* Legacy spellings are part of the API consumed by Xiaomi's other modules. */
#define CountryCN	XIAOMI_COUNTRY_CN
#define CountryGlobal	XIAOMI_COUNTRY_GLOBAL
#define CountryIndia	XIAOMI_COUNTRY_INDIA
#define CountryJapan	XIAOMI_COUNTRY_JAPAN

const char *product_name_get(void);
u32 get_hw_version_platform(void);
u32 get_hw_country_version(void);
u32 get_hw_version_major(void);
u32 get_hw_version_minor(void);
u32 get_hw_version_build(void);
u32 get_hw_project_adc(void);
u32 get_hw_build_adc(void);
u32 get_hw_id_value(void);

#endif /* _XIAOMI_HWID_H_ */
