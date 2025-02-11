#include "../../src/include/Device.h"
#include "../../src/include/iPin.h"
#include "../../src/include/gateAND.h"
#include "../../src/include/gateOR.h"
#include "../../src/include/gateNot.h"
#include "../../src/include/oPin.h"
#include "gtest/gtest.h"

//iPin
TEST(DeviceTEST, IPinGetOutput){
    iPin inPin0, inPin1;
    inPin0.addinputPins(0);
    inPin1.addinputPins(1);

    EXPECT_EQ(inPin0.getOutput(),0);
    EXPECT_EQ(inPin1.getOutput(),1);

    inPin1.addinputPins(0);

    EXPECT_EQ(inPin1.getOutput(),0);
}

//gateNot
TEST(DeviceTEST, GateNotOutput){
    Device* inPin0 = new iPin;
    Device* inPin1 = new iPin;

    inPin0 -> addinputPins(0);
    inPin1 -> addinputPins(1);
    
    gateNot gateNot0, gateNot1;
    gateNot0.addinputPins(inPin0);
    gateNot1.addinputPins(inPin1);

    EXPECT_EQ(gateNot0.getOutput(),1);
    EXPECT_EQ(gateNot1.getOutput(),0);

    delete inPin0;
    delete inPin1;
}

TEST(DeviceTEST, GateANDOutput){
    Device* inPin0 = new iPin;
    Device* inPin1 = new iPin;

    inPin0 -> addinputPins(0);
    inPin1 -> addinputPins(1);
    
    gateAND gateAnd01;
    gateAnd01.addinputPins(inPin0);
    gateAnd01.addinputPins(inPin1);
    EXPECT_EQ(gateAnd01.getOutput(),0);

    gateAND gateAnd11;
    inPin0 -> addinputPins(1);
    gateAnd11.addinputPins(inPin0);
    gateAnd11.addinputPins(inPin1);
    EXPECT_EQ(gateAnd11.getOutput(),1);

    gateAND gateAnd10;
    inPin1 -> addinputPins(0);
    gateAnd10.addinputPins(inPin0);
    gateAnd10.addinputPins(inPin1);
    EXPECT_EQ(gateAnd10.getOutput(),0);

    gateAND gateAnd00;
    inPin0 -> addinputPins(0);
    gateAnd00.addinputPins(inPin0);
    gateAnd00.addinputPins(inPin1);
    EXPECT_EQ(gateAnd00.getOutput(),0);

    delete inPin0;
    delete inPin1; 
}

TEST(DeviceTEST, GateOROutput){
    Device* inPin0 = new iPin;
    Device* inPin1 = new iPin;

    inPin0 -> addinputPins(0);
    inPin1 -> addinputPins(1);
    
    gateOR gateOr01;
    gateOr01.addinputPins(inPin0);
    gateOr01.addinputPins(inPin1);
    EXPECT_EQ(gateOr01.getOutput(),1);

    gateOR gateOr11;
    inPin0 -> addinputPins(1);
    gateOr11.addinputPins(inPin0);
    gateOr11.addinputPins(inPin1);
    EXPECT_EQ(gateOr11.getOutput(),1);

    gateOR gateOr10;
    inPin1 -> addinputPins(0);
    gateOr10.addinputPins(inPin0);
    gateOr10.addinputPins(inPin1);
    EXPECT_EQ(gateOr10.getOutput(),1);

    gateOR gateOr00;
    inPin0 -> addinputPins(0);
    gateOr00.addinputPins(inPin0);
    gateOr00.addinputPins(inPin1);
    EXPECT_EQ(gateOr00.getOutput(),0);

    delete inPin0;
    delete inPin1; 
}

TEST(DeviceTEST, OPinOutput){
    Device* inPin0 = new iPin;
    Device* inPin1 = new iPin;

    inPin0 -> addinputPins(0);
    inPin1 -> addinputPins(1);

    oPin oPin0, oPin1;
    
    oPin0.addinputPins(inPin0);
    oPin1.addinputPins(inPin1);
    EXPECT_EQ(oPin0.getOutput(),0);
    EXPECT_EQ(oPin1.getOutput(),1);

    delete inPin0;
    delete inPin1; 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}