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

void print_section(const char* title, const char* value)
{
    printf("%s%-30s: %s\n", random_color(), title, value);
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
    printf("%s\n", ascii_art);
    printf("%s=== System Information ===\n", random_color());
    print_section("Hostname", hostname);
    print_section("Operating System", os);
    print_section("OS Version", os_version);
    print_section("CPU", cpu);
    print_section("CPU Cores", cpu_cores);
    print_section("Total Memory", total_memory);
    print_section("Used Memory", used_memory);
    print_section("Free Memory", free_memory);
    print_section("Memory Percentage", memory_percentage);
    print_section("Disk Total", disk_total);
    print_section("Disk Used", disk_used);
    print_section("Disk Free", disk_free);
    print_section("Disk Percentage", disk_percentage);
    print_section("Uptime", uptime);
    print_section("Load Average", load_average);
    print_section("Kernel", kernel);
    print_section("Architecture", architecture);
    print_section("Shell", shell);
    print_section("User Name", user_name);
    print_section("IPv4", ipv4);
    print_section("IPv6", ipv6);
    print_section("Installed Packages Count", packages_installed);
    print_section("Current Directory", current_directory);
    print_section("Terminal", terminal);
    print_section("Processor Flags", processor_flags);
    print_section("Total Swap", total_swap);
    print_section("Used Swap", used_swap);
    print_section("Free Swap", free_swap);
    print_section("Swap Percentage", swap_percentage);
    print_section("CPU MHz", cpu_mhz);
    print_section("Virtual Memory", virtual_memory);
    print_section("Disk I/O", disk_io);
    print_section("Network Interfaces", network_interfaces);
    print_section("Timezone", ttimezone);
    print_section("Locale", locale);
    print_section("Graphics Card", graphics_card);
    print_section("Screen Resolution", screen_resolution);
    print_section("System Manufacturer", system_manufacturer);
    print_section("System Product Name", system_product_name);

    //
    // Reset terminal
    //

    printf("\033[0m");

    return 0;
}


/*
 *                          02/10/24
 * Enhanced system information output formatting in sysinfo.c
 *
 * - Added structured section headers for better readability.
 * - Created a `print_section` function to standardize the display of system info.
 * - Improved alignment and spacing for a cleaner visual presentation.
 * - Ensured consistent use of colors for terminal output.
 *
*/
