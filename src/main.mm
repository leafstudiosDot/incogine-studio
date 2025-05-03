#ifdef __APPLE__

#import <Cocoa/Cocoa.h>
#import "about/AboutWindowController.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@property (strong) NSWindow *launcherWindow;
@property (strong) NSWindow *mainWindow;
@property (strong) AboutWindowController *aboutController;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [self setupMenuBar];
    [self showLauncherWindow];
}

- (void)setupMenuBar {
    NSMenu *mainMenu = [[NSMenu alloc] init];
    NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
    [mainMenu addItem:appMenuItem];
    [NSApp setMainMenu:mainMenu];

    NSMenu *appMenu = [[NSMenu alloc] initWithTitle:@"App"];

    // App menu bar - About
    self.aboutController = [[AboutWindowController alloc] init];
    NSString *aboutTitle = [NSString stringWithFormat:@"About Incogine Studio"];
    NSMenuItem *aboutItem = [[NSMenuItem alloc] initWithTitle:aboutTitle action:@selector(showAbout:) keyEquivalent:@""];

    [aboutItem setTarget:self];
    [appMenu addItem:aboutItem];

    // App menu bar - Quit
    NSString *quitTitle = [NSString stringWithFormat:@"Quit Incogine Studio"];
    NSMenuItem *quitItem = [[NSMenuItem alloc] initWithTitle:quitTitle action:@selector(terminate:) keyEquivalent:@"q"];
    [appMenu addItem:quitItem];
    [appMenuItem setSubmenu:appMenu];
}

- (void)showLauncherWindow {
    NSRect launcherRect = NSMakeRect(0, 0, 400, 300);
    self.launcherWindow = [[NSWindow alloc]
        initWithContentRect:launcherRect
                  styleMask:(NSWindowStyleMaskTitled |
                             NSWindowStyleMaskClosable)
                    backing:NSBackingStoreBuffered
                      defer:NO];

    [self.launcherWindow setTitle:@"Incogine Studio"];
    [self.launcherWindow setDelegate:self];
    [self.launcherWindow center];
    [self.launcherWindow setReleasedWhenClosed:NO];
    [self.launcherWindow makeKeyAndOrderFront:nil];

    // Launcher Window - Open Button
    NSButton *launchButton = [[NSButton alloc] initWithFrame:NSMakeRect(130, 120, 140, 40)];
    [launchButton setTitle:@"Open Project"];
    [launchButton setButtonType:NSButtonTypeMomentaryPushIn];
    [launchButton setBezelStyle:NSBezelStyleRounded];
    [launchButton setTarget:self];
    [launchButton setAction:@selector(openMainWindow)];
    [self.launcherWindow.contentView addSubview:launchButton];
}

- (void)showAbout:(id)sender {
    [self.aboutController showAboutWindow];
}

- (void)openMainWindow {
    // Main Window
    NSRect mainRect = NSMakeRect(0, 0, 1280, 720);
    self.mainWindow = [[NSWindow alloc]
        initWithContentRect:mainRect
                  styleMask:(NSWindowStyleMaskTitled |
                             NSWindowStyleMaskClosable |
                             NSWindowStyleMaskResizable)
                    backing:NSBackingStoreBuffered
                      defer:NO];

    [self.mainWindow setTitle:@"Incogine Studio"];
    [self.mainWindow setDelegate:self];
    [self.mainWindow center];
    [self.mainWindow makeKeyAndOrderFront:nil];
    [self.mainWindow setReleasedWhenClosed:NO];

    // Close Launcher
    [self.launcherWindow close];
    self.launcherWindow = nil;
}

- (void)windowWillClose:(NSNotification *)notification {
    if ([notification object] == self.mainWindow) {
        NSWindow *__weak windowRef = self.mainWindow;
        __weak typeof(self) weakSelf = self;
        dispatch_async(dispatch_get_main_queue(), ^{
            if (windowRef) {
                weakSelf.mainWindow = nil;
                [weakSelf showLauncherWindow];
            }
        });
    } else if ([notification object] == self.launcherWindow) {
        [NSApp terminate:self];
    }
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];
        [app run];
    }
    return 0;
}

#endif
