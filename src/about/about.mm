#import "AboutWindowController.h"

@interface AboutWindowController ()
@property (strong) NSWindow *aboutWindow;
@end

@implementation AboutWindowController

- (void)showAboutWindow {
    if (!self.aboutWindow) {
        NSRect rect = NSMakeRect(0, 0, 300, 150);
        self.aboutWindow = [[NSWindow alloc]
            initWithContentRect:rect
                      styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                        backing:NSBackingStoreBuffered
                          defer:NO];

        [self.aboutWindow setTitle:@"About Incogine Studio"];
        [self.aboutWindow center];

        NSTextField *label = [[NSTextField alloc] initWithFrame:NSMakeRect(30, 60, 240, 40)];
        [label setStringValue:@"Incogine Studio v0.0.0.1"];
        [label setBezeled:NO];
        [label setDrawsBackground:NO];
        [label setEditable:NO];
        [label setSelectable:NO];
        [label setAlignment:NSTextAlignmentCenter];
        [label setFont:[NSFont systemFontOfSize:16]];

        [self.aboutWindow.contentView addSubview:label];
    }

    [self.aboutWindow makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

@end
