/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebFormControlElement_h
#define WebFormControlElement_h

#include "public/platform/WebString.h"
#include "WebElement.h"
#include "WebFormElement.h"

namespace blink {

class HTMLFormControlElement;

// Provides readonly access to some properties of a DOM form control element
// node.
class WebFormControlElement : public WebElement {
 public:
  WebFormControlElement() : WebElement() {}
  WebFormControlElement(const WebFormControlElement& e) : WebElement(e) {}

  WebFormControlElement& operator=(const WebFormControlElement& e) {
    WebElement::Assign(e);
    return *this;
  }
  void Assign(const WebFormControlElement& e) { WebElement::Assign(e); }

  BLINK_EXPORT bool IsEnabled() const;
  BLINK_EXPORT bool IsReadOnly() const;
  BLINK_EXPORT WebString FormControlName() const;
  BLINK_EXPORT WebString FormControlType() const;

  BLINK_EXPORT bool IsAutofilled() const;
  BLINK_EXPORT void SetAutofilled(bool);

  // Returns true if autocomplete attribute of the element is not set as "off".
  BLINK_EXPORT bool AutoComplete() const;

  // Sets value for input element, textarea element and select element. For
  // select element it finds the option with value matches the given parameter
  // and make the option as the current selection.
  BLINK_EXPORT void SetValue(const WebString&, bool send_events = false);
  // Sets the autofilled value for input element, textarea element and select
  // element and sends a sequence of events to the element.
  BLINK_EXPORT void SetAutofillValue(const WebString&);
  // Returns value of element. For select element, it returns the value of
  // the selected option if present. If no selected option, an empty string
  // is returned. If element doesn't fall into input element, textarea element
  // and select element categories, a null string is returned.
  BLINK_EXPORT WebString Value() const;
  // Sets suggested value for element. For select element it finds the option
  // with value matches the given parameter and make the option as the suggested
  // selection. The goal of introducing suggested value is to not leak any
  // information to JavaScript.
  BLINK_EXPORT void SetSuggestedValue(const WebString&);
  // Returns suggested value of element. If element doesn't fall into input
  // element, textarea element and select element categories, a null string is
  // returned.
  BLINK_EXPORT WebString SuggestedValue() const;

  // Returns the non-sanitized, exact value inside the text input field
  // or insisde the textarea. If neither input element nor textarea element,
  // a null string is returned.
  BLINK_EXPORT WebString EditingValue() const;

  // Sets character selection range.
  BLINK_EXPORT void SetSelectionRange(int start, int end);
  // Returned value represents a cursor/caret position at the current
  // selection's start for text input field or textarea. If neither input
  // element nor textarea element, 0 is returned.
  BLINK_EXPORT int SelectionStart() const;
  // Returned value represents a cursor/caret position at the current
  // selection's end for text input field or textarea. If neither input
  // element nor textarea element, 0 is returned.
  BLINK_EXPORT int SelectionEnd() const;

  // Returns text-align(only left and right are supported. see crbug.com/482339)
  // of text of element.
  BLINK_EXPORT WebString AlignmentForFormData() const;

  // Returns direction of text of element.
  BLINK_EXPORT WebString DirectionForFormData() const;

  // Returns the name that should be used for the specified |element| when
  // storing autofill data.  This is either the field name or its id, an empty
  // string if it has no name and no id.
  BLINK_EXPORT WebString NameForAutofill() const;

  BLINK_EXPORT WebFormElement Form() const;

#if BLINK_IMPLEMENTATION
  WebFormControlElement(HTMLFormControlElement*);
  WebFormControlElement& operator=(HTMLFormControlElement*);
  operator HTMLFormControlElement*() const;
#endif
};

DECLARE_WEB_NODE_TYPE_CASTS(WebFormControlElement);

}  // namespace blink

#endif