// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import "ios/chrome/browser/ui/bookmarks/bookmark_home_waiting_view.h"

#import "ios/chrome/browser/ui/bookmarks/bookmark_utils_ios.h"
#import "ios/chrome/browser/ui/material_components/activity_indicator.h"
#import "ios/chrome/browser/ui/rtl_geometry.h"
#import "ios/third_party/material_components_ios/src/components/ActivityIndicator/src/MaterialActivityIndicator.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

@interface BookmarkHomeWaitingView ()<MDCActivityIndicatorDelegate>
@property(nonatomic, retain) MDCActivityIndicator* activityIndicator;
@property(nonatomic, copy) ProceduralBlock animateOutCompletionBlock;
@end

@implementation BookmarkHomeWaitingView

@synthesize activityIndicator = _activityIndicator;
@synthesize animateOutCompletionBlock = _animateOutCompletionBlock;

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.backgroundColor = bookmark_utils_ios::mainBackgroundColor();
    self.autoresizingMask =
        UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
  }
  return self;
}

- (void)startWaiting {
  dispatch_time_t delayForIndicatorAppearance =
      dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC));
  dispatch_after(delayForIndicatorAppearance, dispatch_get_main_queue(), ^{
    MDCActivityIndicator* activityIndicator =
        [[MDCActivityIndicator alloc] initWithFrame:CGRectMake(0, 0, 24, 24)];
    self.activityIndicator = activityIndicator;
    self.activityIndicator.delegate = self;
    self.activityIndicator.autoresizingMask =
        UIViewAutoresizingFlexibleLeadingMargin() |
        UIViewAutoresizingFlexibleTopMargin |
        UIViewAutoresizingFlexibleTrailingMargin() |
        UIViewAutoresizingFlexibleBottomMargin;
    self.activityIndicator.center = CGPointMake(
        CGRectGetWidth(self.bounds) / 2, CGRectGetHeight(self.bounds) / 2);
    self.activityIndicator.cycleColors = ActivityIndicatorBrandedCycleColors();
    [self addSubview:self.activityIndicator];
    [self.activityIndicator startAnimating];
  });
}

- (void)stopWaitingWithCompletion:(ProceduralBlock)completion {
  if (self.activityIndicator) {
    self.animateOutCompletionBlock = completion;
    [self.activityIndicator stopAnimating];
  } else if (completion) {
    completion();
  }
}

#pragma mark - MDCActivityIndicatorDelegate

- (void)activityIndicatorAnimationDidFinish:
    (MDCActivityIndicator*)activityIndicator {
  [self.activityIndicator removeFromSuperview];
  self.activityIndicator = nil;
  if (self.animateOutCompletionBlock)
    self.animateOutCompletionBlock();
  self.animateOutCompletionBlock = nil;
}

@end