package com.example.atakhanmobile

data class PlaneEntity(
    var throttle: String,
    var rudder: Int,
    var elevator: Int,
    var ailerionRight: Int,
    var ailerionLeft: Int
){
    fun copy(): PlaneEntity {
        return PlaneEntity(throttle, rudder, elevator, ailerionRight, ailerionLeft)
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (other !is PlaneEntity) return false

        if (throttle != other.throttle) return false
        if (rudder != other.rudder) return false
        if (elevator != other.elevator) return false
        if (ailerionRight != other.ailerionRight) return false
        if (ailerionLeft != other.ailerionLeft) return false

        return true
    }

    override fun hashCode(): Int {
        var result = throttle.hashCode()
        result = 31 * result + rudder
        result = 31 * result + elevator
        result = 31 * result + ailerionRight
        result = 31 * result + ailerionLeft
        return result
    }
}