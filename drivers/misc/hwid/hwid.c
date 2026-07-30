// SPDX-License-Identifier: GPL-2.0
/*
 * Xiaomi hardware identification driver
 *
 * Copyright (C) 2020-2021 Xiaomi, Inc.
 * Copyright (C) 2022 The LineageOS Project
 */

#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <soc/qcom/socinfo.h>

#include "hwid.h"

#define HW_MAJOR_VERSION_SHIFT		16
#define HW_MINOR_VERSION_SHIFT		0
#define HW_COUNTRY_VERSION_SHIFT	20
#define HW_BUILD_VERSION_SHIFT		16

#define HW_MAJOR_VERSION_MASK		0xffff0000
#define HW_MINOR_VERSION_MASK		0x0000ffff
#define HW_COUNTRY_VERSION_MASK		0xfff00000
#define HW_BUILD_VERSION_MASK		0x000f0000

#define SOCINFO_ID_PINEAPPLE		557

static unsigned int hwid_value;
module_param(hwid_value, uint, 0444);
MODULE_PARM_DESC(hwid_value,
		 "Xiaomi hardware ID value for the current build");

static unsigned int project;
module_param(project, uint, 0444);
MODULE_PARM_DESC(project, "Xiaomi hardware project number");

static unsigned int build_adc;
module_param(build_adc, uint, 0444);
MODULE_PARM_DESC(build_adc, "Xiaomi build identification ADC value");

static unsigned int project_adc;
module_param(project_adc, uint, 0444);
MODULE_PARM_DESC(project_adc, "Xiaomi project identification ADC value");

static struct kobject *hwid_kobj;

const char *product_name_get(void)
{
	if (socinfo_get_id() == SOCINFO_ID_PINEAPPLE &&
	    project == HARDWARE_PROJECT_O11)
		return "zorn";

	return "unknown";
}
EXPORT_SYMBOL(product_name_get);

u32 get_hw_project_adc(void)
{
	return project_adc;
}
EXPORT_SYMBOL(get_hw_project_adc);

u32 get_hw_build_adc(void)
{
	return build_adc;
}
EXPORT_SYMBOL(get_hw_build_adc);

u32 get_hw_version_platform(void)
{
	return project;
}
EXPORT_SYMBOL(get_hw_version_platform);

u32 get_hw_id_value(void)
{
	return hwid_value;
}
EXPORT_SYMBOL(get_hw_id_value);

u32 get_hw_country_version(void)
{
	return (hwid_value & HW_COUNTRY_VERSION_MASK) >>
		HW_COUNTRY_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_country_version);

u32 get_hw_version_major(void)
{
	return (hwid_value & HW_MAJOR_VERSION_MASK) >> HW_MAJOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_major);

u32 get_hw_version_minor(void)
{
	return (hwid_value & HW_MINOR_VERSION_MASK) >> HW_MINOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_minor);

u32 get_hw_version_build(void)
{
	return (hwid_value & HW_BUILD_VERSION_MASK) >> HW_BUILD_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_build);

static ssize_t hwid_project_show(struct kobject *kobj,
				 struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "0x%x\n", project);
}

static ssize_t hwid_value_show(struct kobject *kobj,
			       struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "0x%x\n", hwid_value);
}

static ssize_t hwid_project_adc_show(struct kobject *kobj,
				     struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "%u\n", project_adc);
}

static ssize_t hwid_build_adc_show(struct kobject *kobj,
				   struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf, "%u\n", build_adc);
}

static struct kobj_attribute hwid_project_attr = __ATTR_RO(hwid_project);
static struct kobj_attribute hwid_value_attr = __ATTR_RO(hwid_value);
static struct kobj_attribute hwid_project_adc_attr = __ATTR_RO(hwid_project_adc);
static struct kobj_attribute hwid_build_adc_attr = __ATTR_RO(hwid_build_adc);

static struct attribute *hwid_attrs[] = {
	&hwid_project_attr.attr,
	&hwid_value_attr.attr,
	&hwid_project_adc_attr.attr,
	&hwid_build_adc_attr.attr,
	NULL,
};

static const struct attribute_group hwid_attr_group = {
	.attrs = hwid_attrs,
};

static int __init hwid_init(void)
{
	int ret;

	hwid_kobj = kobject_create_and_add("hwid", NULL);
	if (!hwid_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(hwid_kobj, &hwid_attr_group);
	if (ret) {
		kobject_put(hwid_kobj);
		hwid_kobj = NULL;
	}

	return ret;
}
subsys_initcall(hwid_init);

static void __exit hwid_exit(void)
{
	sysfs_remove_group(hwid_kobj, &hwid_attr_group);
	kobject_put(hwid_kobj);
}
module_exit(hwid_exit);

MODULE_AUTHOR("weixiaotian1@xiaomi.com");
MODULE_DESCRIPTION("Xiaomi hardware identification driver");
MODULE_LICENSE("GPL");
