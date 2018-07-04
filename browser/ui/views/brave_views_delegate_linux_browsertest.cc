/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/brave_views_delegate_linux.h"
#include "chrome/grit/chrome_unscaled_resources.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/views/views_delegate.h"

using BraveViewsDelegateViewLinuxBrowserTest = InProcessBrowserTest;

IN_PROC_BROWSER_TEST_F(BraveViewsDelegateViewLinuxBrowserTest, GetDefaultWindowIconTest) {
  auto env = base::Environment::Create();
  views::ViewsDelegate* views_delegate = views::ViewsDelegate::GetInstance();
  auto& rb = ui::ResourceBundle::GetSharedInstance();

#if defined(OFFICIAL_BUILD)
  env->SetVar("CHROME_VERSION_EXTRA", "stable");
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", "beta");
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_BETA)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", "unstable");
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_DEV)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
  env->SetVar("CHROME_VERSION_EXTRA", "dev");
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_DEV)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
#else  // OFFICIAL_BUILD
  EXPECT_EQ(rb.GetImageSkiaNamed(IDR_PRODUCT_LOGO_128_DEVELOPMENT)->bitmap(),
            views_delegate->GetDefaultWindowIcon()->bitmap());
#endif
}

