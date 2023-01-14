// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  ctre::phoenix::led::CANdleConfiguration config;

  config.stripType = ctre::phoenix::led::LEDStripType::RGB; 

  config.brightnessScalar = 0.5; 

  m_candle.ConfigAllSettings(config);

  //m_candle.SetLEDs(0, 0, 255);
}

void Robot::TeleopPeriodic() {
if (m_stick.GetAButtonPressed()){
  std::cout << "A button Presses" << std::endl;
  IncrementAnimation();
}
else if (m_stick.GetBButtonPressed()){
  std::cout << "B button Presses" << std::endl;
  DecrementAnimation();
}

if(m_toAnimate == NULL) {
        m_candle.SetLEDs(255, 0, 0);
    } else {
        m_candle.Animate(*m_toAnimate);
    }
}


void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

void Robot::IncrementAnimation() {
    switch(m_currentAnimation) {
        case ColorFlow: ChangeAnimation(AnimationTypes::Fire); break;
        case Fire: ChangeAnimation(AnimationTypes::Larson); break;
        case Larson: ChangeAnimation(AnimationTypes::Rainbow); break;
        case Rainbow: ChangeAnimation(AnimationTypes::RgbFade); break;
        case RgbFade: ChangeAnimation(AnimationTypes::SingleFade); break;
        case SingleFade: ChangeAnimation(AnimationTypes::Strobe); break;
        case Strobe: ChangeAnimation(AnimationTypes::Twinkle); break;
        case Twinkle: ChangeAnimation(AnimationTypes::TwinkleOff); break;
        case TwinkleOff: ChangeAnimation(AnimationTypes::SetAll); break;
        case SetAll: ChangeAnimation(AnimationTypes::ColorFlow); break;
    }
}
void Robot::DecrementAnimation() {
    switch(m_currentAnimation) {
        case ColorFlow: ChangeAnimation(AnimationTypes::SetAll); break;
        case Fire: ChangeAnimation(AnimationTypes::ColorFlow); break;
        case Larson: ChangeAnimation(AnimationTypes::Fire); break;
        case Rainbow: ChangeAnimation(AnimationTypes::Larson); break;
        case RgbFade: ChangeAnimation(AnimationTypes::Rainbow); break;
        case SingleFade: ChangeAnimation(AnimationTypes::RgbFade); break;
        case Strobe: ChangeAnimation(AnimationTypes::SingleFade); break;
        case Twinkle: ChangeAnimation(AnimationTypes::Strobe); break;
        case TwinkleOff: ChangeAnimation(AnimationTypes::Twinkle); break;
        case SetAll: ChangeAnimation(AnimationTypes::TwinkleOff); break;
    }
}

void Robot::ChangeAnimation(AnimationTypes toChange) {
    m_currentAnimation = toChange;
    
    if(m_toAnimate != NULL) delete m_toAnimate;

    switch(toChange)
    {
        case ColorFlow:
            m_toAnimate = new ctre::phoenix::led::ColorFlowAnimation(128, 20, 70, 0, 0.7, LedCount, ctre::phoenix::led::ColorFlowAnimation::Direction::Forward);
            break;
        case Fire:
            m_toAnimate = new ctre::phoenix::led::FireAnimation(1.0, 0.5, LedCount, 0.7, 0.0);
            break;
        case Larson:
            m_toAnimate = new ctre::phoenix::led::LarsonAnimation(0, 255, 46, 0, 1, LedCount, ctre::phoenix::led::LarsonAnimation::BounceMode::Front, 3);
            break;
        case Rainbow:
            m_toAnimate = new ctre::phoenix::led::RainbowAnimation(1, 1.0, LedCount);
            break;
        case RgbFade:
            m_toAnimate = new ctre::phoenix::led::RgbFadeAnimation(0.7, 0.4, LedCount);
            break;
        case SingleFade:
            m_toAnimate = new ctre::phoenix::led::SingleFadeAnimation(50, 2, 200, 0, 0.5, LedCount);
            break;
        case Strobe:
            m_toAnimate = new ctre::phoenix::led::StrobeAnimation(240, 10, 180, 0, 98.0 / 256.0, LedCount);
            break;
        case Twinkle:
            m_toAnimate = new ctre::phoenix::led::TwinkleAnimation(30, 70, 60, 0, 0.4, LedCount, ctre::phoenix::led::TwinkleAnimation::TwinklePercent::Percent6);
            break;
        case TwinkleOff:
            m_toAnimate = new ctre::phoenix::led::TwinkleOffAnimation(70, 90, 175, 0, 0.8, LedCount, ctre::phoenix::led::TwinkleOffAnimation::TwinkleOffPercent::Percent100);
            break;
        default:
        case SetAll:
            m_toAnimate = NULL;
            break;
    }
    std::cout << "Changed to " << std::to_string(m_currentAnimation) << std::endl;
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
