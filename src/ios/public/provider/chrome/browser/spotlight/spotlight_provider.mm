// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import "ios/public/provider/chrome/browser/spotlight/spotlight_provider.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

bool SpotlightProvider::IsSpotlightEnabled() {
  return false;
}

NSString* SpotlightProvider::GetBookmarkDomain() {
  return nil;
}

NSString* SpotlightProvider::GetTopSitesDomain() {
  return nil;
}

NSString* SpotlightProvider::GetActionsDomain() {
  return nil;
}

NSString* SpotlightProvider::GetCustomAttributeItemID() {
  return nil;
}

NSArray* SpotlightProvider::GetAdditionalKeywords() {
  return nil;
}