/*
 * Copyright (c) 2023, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/FlyString.h>
#include <AK/NonnullRefPtr.h>
#include <LibJS/Heap/GCPtr.h>
#include <LibWeb/CSS/CSSKeyframeRule.h>
#include <LibWeb/CSS/CSSRule.h>
#include <LibWeb/Forward.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::CSS {

// https://drafts.csswg.org/css-animations/#interface-csskeyframesrule
class CSSKeyframesRule final : public CSSRule {
    WEB_PLATFORM_OBJECT(CSSKeyframesRule, CSSRule);

public:
    static WebIDL::ExceptionOr<JS::NonnullGCPtr<CSSKeyframesRule>> create(JS::Realm& realm, FlyString name, Vector<JS::NonnullGCPtr<CSSKeyframeRule>> keyframes)
    {
        return MUST_OR_THROW_OOM(realm.heap().allocate<CSSKeyframesRule>(realm, realm, move(name), move(keyframes)));
    }

    virtual ~CSSKeyframesRule() = default;

    virtual Type type() const override { return Type::Keyframes; };

    Vector<JS::NonnullGCPtr<CSSKeyframeRule>> const& keyframes() const { return m_keyframes; }
    FlyString const& name() const { return m_name; }

private:
    CSSKeyframesRule(JS::Realm& realm, FlyString name, Vector<JS::NonnullGCPtr<CSSKeyframeRule>> keyframes)
        : CSSRule(realm)
        , m_name(move(name))
        , m_keyframes(move(keyframes))
    {
    }

    virtual void visit_edges(Visitor&) override;

    virtual JS::ThrowCompletionOr<void> initialize(JS::Realm&) override;
    virtual DeprecatedString serialized() const override;

    FlyString m_name;
    Vector<JS::NonnullGCPtr<CSSKeyframeRule>> m_keyframes;
};

template<>
inline bool CSSRule::fast_is<CSSKeyframesRule>() const { return type() == CSSRule::Type::Keyframes; }

}
