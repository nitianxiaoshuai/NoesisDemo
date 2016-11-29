////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSFORM_H__
#define __GUI_TRANSFORM_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsCore/TypeMetaData.h>


namespace Noesis
{

// Forward declarations
//@{
namespace Math
{
template<class T> class Transform2;
typedef Noesis::Math::Transform2<NsFloat32> Transform2f;
}
//@}

namespace Gui
{

// TODO: [srodriguez] Transform must derive from GeneralTransform

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Transform. Defines functionality that enables transformations in a 2-D plane. Transformations
/// include rotation (RotateTransform), 
/// scale (ScaleTransform), 
/// skew (SkewTransform), and translation (TranslateTransform).
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.transform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Transform: public Animatable
{
public:
    /// Constructor
    Transform();

    /// Destructor. Base classes are abstract classes. Destructor is pure virtual
    virtual ~Transform() = 0;
    
    /// Parses a string value to create an instance of a MatrixTransform
    static Ptr<Transform> Parse(const NsChar* str);
    static NsBool TryParse(const NsChar* str, Ptr<BaseComponent>& result);

    /// Gets Identity transform object
    /// \prop
    static Transform* GetIdentity();

    /// Gets the transformation matrix defined by a transform object
    virtual Math::Transform2f GetTransform() const = 0;

private:
    /// Base classes are non-copyable objects
    //@{
    Transform(const Transform&);
    Transform& operator=(const Transform&);
    //@}

    NS_DECLARE_REFLECTION(Transform, Animatable)
};

}
}

#endif
