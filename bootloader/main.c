#include <common.h>
#include <utils/printf.h>

EFI_HANDLE *imageHandle;
EFI_SYSTEM_TABLE *systemTable;

EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *stdout;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL *stdin;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *stderr;

int _fltused = 0;

void _putchar(char c) {
    CHAR16 str[2];
    str[0] = (CHAR16)c;
    str[1] = '\0';

    if (c == '\n')
    {
        stdout->OutputString(stdout, L"\r");
    }

    stdout->OutputString(stdout, str);
}

EFI_STATUS boot_entry(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) { 
    // Setup global variables.
    imageHandle = &ImageHandle;
    systemTable = SystemTable;
    stdout = systemTable->ConOut;
    stdin = systemTable->ConIn;
    stderr = systemTable->StdErr;

    // Setup the screen.
    stdout->SetAttribute(stdout, EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK);
    stdout->SetCursorPosition(stdout, 0, 0);
    stdout->ClearScreen(stdout);

    // Print a welcome message.
    printf("Hello, this is an epic UEFI bootloader!\n");

    // Main loop.
    while(1) {
        // do nothing.
    }
    return EFI_SUCCESS;
}
