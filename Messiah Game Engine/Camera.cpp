//
//  Camera.cpp
//  Game Editor
//
//  Created by Attila Varga on 03/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//



#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace DMGS;

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera() :
_position(0.0f, 0.0f, 1.0f),
_horizontalAngle(0.0f),
_verticalAngle(0.0f),
_fieldOfView(50.0f),
_nearPlane(0.01f),
_farPlane(100.0f),
_viewportAspectRatio(4.0f/3.0f)
{
    isMoving = false;
    isMovingForward = false;
    isMovingBackward = false;
    isMovingLeft = false;
    isMovingRight = false;
    
    mDirection = glm::vec3();
}

const glm::vec3& Camera::position() const {
    return _position;
}

void Camera::setPosition(const glm::vec3& position) {
    _position = position;
}

void Camera::offsetPosition(const glm::vec3& offset) {
    _position += offset;
}

float Camera::fieldOfView() const {
    return _fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView) {
    assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
    _fieldOfView = fieldOfView;
}

float Camera::nearPlane() const {
    return _nearPlane;
}

float Camera::farPlane() const {
    return _farPlane;
}

void Camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    _nearPlane = nearPlane;
    _farPlane = farPlane;
}

glm::mat4 Camera::orientation() const {
    glm::mat4 orientation;
    orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0,1,0));
    return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle) {
    _horizontalAngle += rightAngle;
    _verticalAngle += upAngle;
    normalizeAngles();
}

void Camera::lookAt(glm::vec3 position) {
    assert(position != _position);
    glm::vec3 direction = glm::normalize(position - _position);
    _verticalAngle = glm::radians(asinf(-direction.y));
    _horizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
    normalizeAngles();
}

float Camera::viewportAspectRatio() const {
    return _viewportAspectRatio;
}

void Camera::setViewportAspectRatio(float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0);
    _viewportAspectRatio = viewportAspectRatio;
}

glm::vec3 Camera::forward() const {
    glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
    glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 Camera::up() const {
    glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}

glm::mat4 Camera::matrix() const {
    return projection() * view();
}

glm::mat4 Camera::projection() const {
    return glm::perspective(glm::radians(_fieldOfView), _viewportAspectRatio, _nearPlane, _farPlane);
}

glm::mat4 Camera::view() const {
    return orientation() * glm::translate(glm::mat4(), -_position);
}

void Camera::normalizeAngles() {
    _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(_horizontalAngle < 0.0f)
        _horizontalAngle += 360.0f;
    
    if(_verticalAngle > MaxVerticalAngle)
        _verticalAngle = MaxVerticalAngle;
    else if(_verticalAngle < -MaxVerticalAngle)
        _verticalAngle = -MaxVerticalAngle;
}
//
//
void Camera::setDirection(glm::vec3 direction)
{
    mDirection = direction;
}

void Camera::setDirection(float x, float y, float z)
{
    mDirection = glm::vec3(x,y,z);
}
//
//
void Camera::stopCamera()
{
    Moving(false);
    isMovingForward = false;
    isMovingBackward = false;
    isMovingLeft = false;
    isMovingRight = false;
}

void Camera::moveForward()
{
    isMoving = true;
    isMovingForward = true;
}

void Camera::moveBackward()
{
    isMoving = true;
    isMovingBackward = true;
}
void Camera::moveLeft()
{
    isMoving = true;
    isMovingLeft = true;
}

void Camera::moveRight()
{
    isMoving = true;
    isMovingRight = true;
}

void Camera::update(float elapsedTime)
{
    if(isMoving)
    {
        if (isMovingForward)
        {
            offsetPosition(elapsedTime * 5.0f * forward());
        }
        else if (isMovingBackward)
        {
            offsetPosition(elapsedTime * 5.0f * -forward());
        }
        if (isMovingLeft)
        {
            offsetPosition(elapsedTime * 5.0f * -right());
        }
        else if (isMovingRight)
        {
            offsetPosition(elapsedTime * 5.0f * right());
        }
    }
    
}
