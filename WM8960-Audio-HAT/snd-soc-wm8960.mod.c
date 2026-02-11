#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd408e46e, "regcache_sync" },
	{ 0xfcda6815, "regmap_write" },
	{ 0x53af9550, "devm_kmalloc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc879b662, "snd_soc_component_read" },
	{ 0xda56257e, "snd_soc_put_enum_double" },
	{ 0x6cd8f119, "devm_clk_get" },
	{ 0xd94c342b, "snd_soc_component_write" },
	{ 0xe4ffc439, "devm_snd_soc_register_component" },
	{ 0x7c9a7371, "clk_prepare" },
	{ 0x92997ed8, "_printk" },
	{ 0x54842fc8, "__devm_regmap_init_i2c" },
	{ 0x36b627fa, "snd_soc_get_enum_double" },
	{ 0xc495e891, "i2c_register_driver" },
	{ 0xfcf7bb8c, "snd_soc_info_volsw" },
	{ 0x59e5070d, "__do_div64" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x4b913484, "snd_ctl_boolean_mono_info" },
	{ 0x88564db5, "_dev_err" },
	{ 0x99bb4d2c, "snd_soc_dapm_put_volsw" },
	{ 0x4e269a3, "of_find_property" },
	{ 0xc3115d3d, "snd_soc_add_component_controls" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x865ce8ac, "snd_soc_dapm_add_routes" },
	{ 0x6178637c, "snd_soc_info_enum_double" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xb362428c, "snd_soc_get_volsw" },
	{ 0xfba72691, "snd_soc_put_volsw" },
	{ 0xcfe296b4, "snd_soc_component_update_bits" },
	{ 0xd6ba98d4, "snd_soc_dapm_new_controls" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0xb6e6d99d, "clk_disable" },
	{ 0xdb52cc34, "regmap_update_bits_base" },
	{ 0x7e14d838, "snd_soc_dapm_get_volsw" },
	{ 0xcec89219, "i2c_del_driver" },
	{ 0x815588a6, "clk_enable" },
	{ 0x2acda8a0, "snd_soc_params_to_bclk" },
	{ 0xf9a482f9, "msleep" },
	{ 0xe56a9336, "snd_pcm_format_width" },
	{ 0xb077e70a, "clk_unprepare" },
	{ 0xf1ce2f51, "module_layout" },
};

MODULE_INFO(depends, "snd-soc-core,regmap-i2c,snd,snd-pcm");

MODULE_ALIAS("i2c:wm8960");
MODULE_ALIAS("of:N*T*Cwlf,wm8960");
MODULE_ALIAS("of:N*T*Cwlf,wm8960C*");

MODULE_INFO(srcversion, "84FE1B438367A04968189F2");
