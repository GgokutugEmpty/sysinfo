/*
Author : A.Goktug
Create Date : 27 /09/2024
File : sysinfo.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "var.h"
const char* random_color()
{
    static const char* colors[] =
    {
        "\033[31m", // Red
        "\033[32m", // Green
        "\033[33m", // Yellow
        "\033[34m", // Blue
        "\033[35m", // Magenta
        "\033[36m", // Cyan
        "\033[37m"  // White
    };

    return colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
}
void get_command_output(const char *command, char *output, size_t size)
{
    FILE *fp = popen(command, "r");
    if (fp != NULL)
    {
        fgets(output, size, fp);
        pclose(fp);
    } else
    {
        snprintf(output, size, "Error: Command could not be executed.");
    }
}

int main()
{
    srand(time(NULL));

    get_command_output("hostname", hostname, sizeof(hostname));
    get_command_output("uname -s", os, sizeof(os));
    get_command_output("uname -r", os_version, sizeof(os_version));
    get_command_output("lscpu | grep 'Model name' | awk -F: '{print $2}'", cpu, sizeof(cpu));
    get_command_output("lscpu | grep '^CPU(s):' | awk '{print $2}'", cpu_cores, sizeof(cpu_cores));
    get_command_output("free -h | grep 'Mem:' | awk '{print $2}'", total_memory, sizeof(total_memory));
    get_command_output("free -h | grep 'Mem:' | awk '{print $3}'", used_memory, sizeof(used_memory));
    get_command_output("free -h | grep 'Mem:' | awk '{print $7}'", free_memory, sizeof(free_memory));
    get_command_output("free | grep Mem | awk '{print $3/$2 * 100.0}'", memory_percentage, sizeof(memory_percentage));
    get_command_output("df -h / | grep / | awk '{ print $2 }'", disk_total, sizeof(disk_total));
    get_command_output("df -h / | grep / | awk '{ print $3 }'", disk_used, sizeof(disk_used));
    get_command_output("df -h / | grep / | awk '{ print $4 }'", disk_free, sizeof(disk_free));
    get_command_output("df -h / | grep / | awk '{ print $5 }'", disk_percentage, sizeof(disk_percentage));
    get_command_output("uptime -p", uptime, sizeof(uptime));
    get_command_output("cat /proc/loadavg | awk '{print $1, $2, $3}'", load_average, sizeof(load_average));
    get_command_output("uname -v", kernel, sizeof(kernel));
    get_command_output("uname -m", architecture, sizeof(architecture));
    get_command_output("echo $SHELL | awk -F/ '{print $NF}'", shell, sizeof(shell));
    get_command_output("hostname -f", hostname_full, sizeof(hostname_full));
    get_command_output("whoami", user_name, sizeof(user_name));
    get_command_output("hostname -I | awk '{print $1}'", ipv4, sizeof(ipv4));
    get_command_output("hostname -I | awk '{print $2}'", ipv6, sizeof(ipv6));
    get_command_output("dpkg --get-selections | grep -v deinstall | wc -l", packages_installed, sizeof(packages_installed));
    get_command_output("echo $PATH | tr ':' '\\n' | wc -l", package_manager, sizeof(package_manager));
    get_command_output("pwd", current_directory, sizeof(current_directory));
    get_command_output("echo $TERM", terminal, sizeof(terminal));
    get_command_output("lscpu | grep 'Flags' | awk -F: '{print $2}'", processor_flags, sizeof(processor_flags));
    get_command_output("swapon --show=SIZE --bytes | awk '{print $1}' | tail -n 1", swap_total, sizeof(swap_total));
    get_command_output("free -h | grep 'Swap:' | awk '{print $3}'", swap_used, sizeof(swap_used));
    get_command_output("free -h | grep 'Swap:' | awk '{print $4}'", swap_free, sizeof(swap_free));
    get_command_output("free | grep Swap | awk '{print $3/$2 * 100.0}'", swap_percentage, sizeof(swap_percentage));
    get_command_output("lscpu | grep 'CPU MHz' | awk '{print $3}'", cpu_mhz, sizeof(cpu_mhz));
    get_command_output("free -h | grep 'Mem:' | awk '{print $3/$2 * 100.0}'", virtual_memory, sizeof(virtual_memory));
    get_command_output("free -h | grep 'Swap:' | awk '{print $2}'", total_swap, sizeof(total_swap));
    get_command_output("free -h | grep 'Swap:' | awk '{print $3}'", used_swap, sizeof(used_swap));
    get_command_output("free -h | grep 'Swap:' | awk '{print $4}'", free_swap, sizeof(free_swap));
    get_command_output("iostat -x | awk 'NR==4{print $1}'", disk_io, sizeof(disk_io));
    get_command_output("ip -o link show | awk -F': ' '{print $2}'", network_interfaces, sizeof(network_interfaces));
    get_command_output("timedatectl show --property=Timezone --value", ttimezone, sizeof(ttimezone));
    get_command_output("locale", locale, sizeof(locale));
    get_command_output("lspci | grep VGA | awk -F: '{print $2}'", graphics_card, sizeof(graphics_card));
    get_command_output("xrandr | grep '*' | awk '{print $1}'", screen_resolution, sizeof(screen_resolution));
    get_command_output("sudo dmidecode -s system-manufacturer", system_manufacturer, sizeof(system_manufacturer));
    get_command_output("sudo dmidecode -s system-product-name", system_product_name, sizeof(system_product_name));
    /*------------------------------------------------------------------------------------------------------------------*/
    printf("%s", ascii_art);
    printf("%sHostname: %s", random_color(), hostname);
    printf("%sOperating System: %s", random_color(), os);
    printf("%sOperating System Version: %s", random_color(), os_version);
    printf("%sCPU: %s", random_color(), cpu);
    printf("%sCPU Core Count: %s", random_color(), cpu_cores);
    printf("%sTotal Memory: %s", random_color(), total_memory);
    printf("%sUsed Memory: %s", random_color(), used_memory);
    printf("%sFree Memory: %s", random_color(), free_memory);
    printf("%sMemory Percentage: %s%%\n", random_color(), memory_percentage);
    printf("%sDisk Total: %s", random_color(), disk_total);
    printf("%sDisk Used: %s", random_color(), disk_used);
    printf("%sDisk Free: %s", random_color(), disk_free);
    printf("%sDisk Percentage: %s\n", random_color(), disk_percentage);
    printf("%sUptime: %s", random_color(), uptime);
    printf("%sLoad Average: %s\n", random_color(), load_average);
    printf("%sKernel: %s", random_color(), kernel);
    printf("%sArchitecture: %s", random_color(), architecture);
    printf("%sShell: %s", random_color(), shell);
    printf("%sFull Hostname: %s", random_color(), hostname_full);
    printf("%sUser Name: %s", random_color(), user_name);
    printf("%sIPv4: %s", random_color(), ipv4);
    printf("%sIPv6: %s", random_color(), ipv6);
    printf("%sInstalled Packages Count: %s\n", random_color(), packages_installed);
    printf("%sPackage Manager: %s\n", random_color(), package_manager);
    printf("%sCurrent Directory: %s", random_color(), current_directory);
    printf("%sTerminal: %s", random_color(), terminal);
    printf("%sProcessor Flags: %s", random_color(), processor_flags);
    printf("%sTotal Swap: %s", random_color(), swap_total);
    printf("%sUsed Swap: %s", random_color(), swap_used);
    printf("%sFree Swap: %s", random_color(), swap_free);
    printf("%sSwap Percentage: %s%%\n", random_color(), swap_percentage);
    printf("%sCPU MHz: %s\n", random_color(), cpu_mhz);
    printf("%sVirtual Memory: %s%%\n", random_color(), virtual_memory);
    printf("%sTotal Swap: %s", random_color(), total_swap);
    printf("%sUsed Swap: %s", random_color(), used_swap);
    printf("%sFree Swap: %s", random_color(), free_swap);
    printf("%sDisk I/O: %s\n", random_color(), disk_io);
    printf("%sNetwork Interfaces: %s\n", random_color(), network_interfaces);
    printf("%sTimezone: %s\n", random_color(), ttimezone);
    printf("%sLocale: %s\n", random_color(), locale);
    printf("%sGraphics Card: %s", random_color(), graphics_card);
    printf("%sScreen Resolution: %s", random_color(), screen_resolution);
    printf("%sSystem Manufacturer: %s", random_color(), system_manufacturer);
    printf("%sSystem Product Name: %s", random_color(), system_product_name);

    //
    // Reset terminal
    //

    printf("\033[0m");

    return 0;
}
