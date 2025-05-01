QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Box2D/Collision/Shapes/b2ChainShape.cpp \
    Box2D/Collision/Shapes/b2CircleShape.cpp \
    Box2D/Collision/Shapes/b2EdgeShape.cpp \
    Box2D/Collision/Shapes/b2PolygonShape.cpp \
    Box2D/Collision/b2BroadPhase.cpp \
    Box2D/Collision/b2CollideCircle.cpp \
    Box2D/Collision/b2CollideEdge.cpp \
    Box2D/Collision/b2CollidePolygon.cpp \
    Box2D/Collision/b2Collision.cpp \
    Box2D/Collision/b2Distance.cpp \
    Box2D/Collision/b2DynamicTree.cpp \
    Box2D/Collision/b2TimeOfImpact.cpp \
    Box2D/Common/b2BlockAllocator.cpp \
    Box2D/Common/b2Draw.cpp \
    Box2D/Common/b2Math.cpp \
    Box2D/Common/b2Settings.cpp \
    Box2D/Common/b2StackAllocator.cpp \
    Box2D/Common/b2Timer.cpp \
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    Box2D/Dynamics/Contacts/b2Contact.cpp \
    Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    Box2D/Dynamics/Joints/b2GearJoint.cpp \
    Box2D/Dynamics/Joints/b2Joint.cpp \
    Box2D/Dynamics/Joints/b2MotorJoint.cpp \
    Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    Box2D/Dynamics/b2Body.cpp \
    Box2D/Dynamics/b2ContactManager.cpp \
    Box2D/Dynamics/b2Fixture.cpp \
    Box2D/Dynamics/b2Island.cpp \
    Box2D/Dynamics/b2World.cpp \
    Box2D/Dynamics/b2WorldCallbacks.cpp \
    Box2D/Rope/b2Rope.cpp \
    brazil.cpp \
    brazilharvest.cpp \
    brazilintro.cpp \
    braziloutro.cpp \
    brazilpresspast.cpp \
    caribbeanboiling.cpp \
    caribbeanbottling.cpp \
    caribbeandistillation.cpp \
    caribbeanfermentation.cpp \
    caribbeanharvest.cpp \
    caribbeanintro.cpp \
    caribbeanmaturation.cpp \
    creditswindow.cpp \
    germanybottle.cpp \
    germanyferment.cpp \
    germanyhop.cpp \
    germanyintro.cpp \
    germanylaut.cpp \
    germanymalt.cpp \
    germanymash.cpp \
    germanymature.cpp \
    germanymill.cpp \
    ethiopiaIntro.cpp \
    ethiopiaoutro.cpp \
    ethiopiaphysics.cpp \
    japan.cpp \
    japanintro.cpp \
    japanoutro.cpp \
    japanpresspast.cpp \
    main.cpp \
    mainwindow.cpp \
    mexico.cpp \
    mexicocookpress.cpp \
    mexicoharvest.cpp \
    mexicointro.cpp \
    mexicooutro.cpp \
    startwindow.cpp

HEADERS += \
    Box2D/Box2D.h \
    Box2D/Collision/Shapes/b2ChainShape.h \
    Box2D/Collision/Shapes/b2CircleShape.h \
    Box2D/Collision/Shapes/b2EdgeShape.h \
    Box2D/Collision/Shapes/b2PolygonShape.h \
    Box2D/Collision/Shapes/b2Shape.h \
    Box2D/Collision/b2BroadPhase.h \
    Box2D/Collision/b2Collision.h \
    Box2D/Collision/b2Distance.h \
    Box2D/Collision/b2DynamicTree.h \
    Box2D/Collision/b2TimeOfImpact.h \
    Box2D/Common/b2BlockAllocator.h \
    Box2D/Common/b2Draw.h \
    Box2D/Common/b2GrowableStack.h \
    Box2D/Common/b2Math.h \
    Box2D/Common/b2Settings.h \
    Box2D/Common/b2StackAllocator.h \
    Box2D/Common/b2Timer.h \
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    Box2D/Dynamics/Contacts/b2CircleContact.h \
    Box2D/Dynamics/Contacts/b2Contact.h \
    Box2D/Dynamics/Contacts/b2ContactSolver.h \
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    Box2D/Dynamics/Contacts/b2PolygonContact.h \
    Box2D/Dynamics/Joints/b2DistanceJoint.h \
    Box2D/Dynamics/Joints/b2FrictionJoint.h \
    Box2D/Dynamics/Joints/b2GearJoint.h \
    Box2D/Dynamics/Joints/b2Joint.h \
    Box2D/Dynamics/Joints/b2MotorJoint.h \
    Box2D/Dynamics/Joints/b2MouseJoint.h \
    Box2D/Dynamics/Joints/b2PrismaticJoint.h \
    Box2D/Dynamics/Joints/b2PulleyJoint.h \
    Box2D/Dynamics/Joints/b2RevoluteJoint.h \
    Box2D/Dynamics/Joints/b2RopeJoint.h \
    Box2D/Dynamics/Joints/b2WeldJoint.h \
    Box2D/Dynamics/Joints/b2WheelJoint.h \
    Box2D/Dynamics/b2Body.h \
    Box2D/Dynamics/b2ContactManager.h \
    Box2D/Dynamics/b2Fixture.h \
    Box2D/Dynamics/b2Island.h \
    Box2D/Dynamics/b2TimeStep.h \
    Box2D/Dynamics/b2World.h \
    Box2D/Dynamics/b2WorldCallbacks.h \
    Box2D/Rope/b2Rope.h \
    brazil.h \
    brazilharvest.h \
    brazilintro.h \
    braziloutro.h \
    brazilpresspast.h \
    caribbeanboiling.h \
    caribbeanbottling.h \
    caribbeandistillation.h \
    caribbeanfermentation.h \
    caribbeanharvest.h \
    caribbeanintro.h \
    caribbeanmaturation.h \
    creditswindow.h \
    germanybottle.h \
    germanyferment.h \
    germanyhop.h \
    germanyintro.h \
    germanylaut.h \
    germanymalt.h \
    germanymash.h \
    germanymature.h \
    germanymill.h \
    ethiopiaIntro.h \
    ethiopiaoutro.h \
    ethiopiaphysics.h \
    japan.h \
    japanintro.h \
    japanoutro.h \
    japanpresspast.h \
    mainwindow.h \
    mexico.h \
    mexicocookpress.h \
    mexicoharvest.h \
    mexicointro.h \
    mexicooutro.h \
    startwindow.h

FORMS += \
    brazil.ui \
    brazilharvest.ui \
    brazilintro.ui \
    braziloutro.ui \
    brazilpresspast.ui \
    caribbeanboiling.ui \
    caribbeanbottling.ui \
    caribbeandistillation.ui \
    caribbeanfermentation.ui \
    caribbeanharvest.ui \
    caribbeanintro.ui \
    caribbeanmaturation.ui \
    creditswindow.ui \
    germanybottle.ui \
    germanyferment.ui \
    germanyhop.ui \
    germanyintro.ui \
    germanylaut.ui \
    germanymalt.ui \
    germanymash.ui \
    germanymature.ui \
    germanymill.ui \
    ethiopiaIntro.ui \
    ethiopiaoutro.ui \
    ethiopiaphysics.ui \
    japan.ui \
    japanintro.ui \
    japanoutro.ui \
    japanpresspast.ui \
    mainwindow.ui \
    mexico.ui \
    mexicocookpress.ui \
    mexicoharvest.ui \
    mexicointro.ui \
    mexicooutro.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Box2D/Box2DConfig.cmake \
    Box2D/CMakeLists.txt

RESOURCES += \
    Pictures.qrc
