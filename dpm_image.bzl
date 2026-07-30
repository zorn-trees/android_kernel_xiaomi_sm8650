load("@//build/kernel/kleaf:hermetic_tools.bzl", "hermetic_genrule")

def define_dpm_image(tv):
    target = tv.split("_")[0]
    hermetic_genrule(
        name = "{}_dpm_image".format(tv),
        srcs = [
            "//kernel/xiaomi/sm8650:{}_build_config".format(tv),
            "//kernel/xiaomi/sm8650:{}/{}-dpm-overlay.dtbo".format(tv, target),
        ],
        outs = ["{}/dpm.img".format(tv)],
        cmd = """
            # Stub out append_cmd
            append_cmd() {{
              :
            }}

            set +u
            source "$(location //kernel/xiaomi/sm8650:{tv}_build_config)"
            set -u

            $(location //prebuilts/kernel-build-tools:linux-x86/bin/mkdtboimg) \
                    create "$@" --page_size="$$PAGE_SIZE" \
                    "$(location //kernel/xiaomi/sm8650:{tv}/{target}-dpm-overlay.dtbo)"
        """.format(
            tv = tv,
            target = target,
        ),
        tools = [
            "//prebuilts/kernel-build-tools:linux-x86/bin/mkdtboimg",
        ],
    )
