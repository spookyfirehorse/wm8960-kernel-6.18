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
	{ 0x1d2e0155, "simple_util_set_dailink_name" },
	{ 0x5b58d075, "snd_soc_of_parse_tdm_slot" },
	{ 0x4d5430b2, "simple_util_canonicalize_platform" },
	{ 0x11a89355, "simple_util_startup" },
	{ 0x53af9550, "devm_kmalloc" },
	{ 0x479ef66b, "of_node_put" },
	{ 0xc8e8d22c, "of_property_read_variable_u32_array" },
	{ 0xd187f3e0, "platform_driver_unregister" },
	{ 0xcc28907, "simple_util_parse_convert" },
	{ 0xc358aaf8, "snprintf" },
	{ 0xafe1aad7, "simple_util_parse_widgets" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x46ab9c90, "simple_util_parse_daifmt" },
	{ 0x6ebd5a45, "of_get_parent" },
	{ 0xf4554fed, "of_node_get" },
	{ 0xc7a39a41, "snd_soc_of_parse_node_prefix" },
	{ 0x60584686, "simple_util_init_priv" },
	{ 0x1ea7d5ed, "simple_util_hw_params" },
	{ 0x135c68f7, "of_get_next_child" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x5527668e, "snd_soc_of_parse_aux_devs" },
	{ 0xdff78fb3, "simple_util_clean_reference" },
	{ 0x37f78dcc, "simple_util_parse_pin_switches" },
	{ 0xcd19b0, "simple_util_init_jack" },
	{ 0x4fa45fa3, "of_get_child_by_name" },
	{ 0x2d25c4ae, "simple_util_be_hw_params_fixup" },
	{ 0xe860c9cb, "devm_kfree" },
	{ 0x88564db5, "_dev_err" },
	{ 0x6af16ee1, "__of_parse_phandle_with_args" },
	{ 0x26556cb6, "simple_util_parse_clk" },
	{ 0x5cf4bbfa, "simple_util_parse_routing" },
	{ 0xfd16a811, "of_device_is_available" },
	{ 0x4c7e4f2f, "snd_soc_of_get_dai_name" },
	{ 0xe4a96d7a, "simple_util_canonicalize_cpu" },
	{ 0x5f754e5a, "memset" },
	{ 0x35447540, "simple_util_parse_card_name" },
	{ 0x12efb751, "simple_util_shutdown" },
	{ 0xe35b87e3, "__platform_driver_register" },
	{ 0x32aeff5c, "simple_util_remove" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x9c52a4ae, "snd_soc_pm_ops" },
	{ 0x13fea9a0, "of_device_get_match_data" },
	{ 0x1fb839f2, "devm_snd_soc_register_card" },
	{ 0x8d0fd208, "simple_util_dai_init" },
	{ 0xf1ce2f51, "module_layout" },
};

MODULE_INFO(depends, "snd-soc-simple-card-utils,snd-soc-core");

MODULE_ALIAS("of:N*T*Csimple-audio-card");
MODULE_ALIAS("of:N*T*Csimple-audio-cardC*");
MODULE_ALIAS("of:N*T*Csimple-scu-audio-card");
MODULE_ALIAS("of:N*T*Csimple-scu-audio-cardC*");

MODULE_INFO(srcversion, "997921DB87D831BCD78C2A9");
