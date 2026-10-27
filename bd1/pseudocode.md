FUNCTION Main
    DECLARE rate AS Real
    DECLARE hours[7] AS Real
    DECLARE dayNames[7] AS String
    DECLARE totalhours AS Real
    DECLARE maxDay AS Integer
    DECLARE deduction AS Real
    DECLARE i AS Integer
    DECLARE maxhours AS Real
    DECLARE regularhours AS Real
    DECLARE overtimehours AS Real
    DECLARE grosspay AS Real
    DECLARE netpay AS Real
    DECLARE accumulated AS Real
    DECLARE before AS Real
    DECLARE after AS Real
    DECLARE regulartoday AS Real
    DECLARE overtimetoday AS Real
    DECLARE daypay AS Real

    totalhours = 0
    maxDay = 0

    dayNames[0] = "monday"
    dayNames[1] = "tuesday"
    dayNames[2] = "wednesday"
    dayNames[3] = "thursday"
    dayNames[4] = "friday"
    dayNames[5] = "saturday"
    dayNames[6] = "sunday"

    OUTPUT "Hourly rate (MNT):"
    DO
        INPUT rate
    WHILE rate <= 0

    OUTPUT "Deduction percentage (0-100):"
    DO
        INPUT deduction
    WHILE deduction < 0 OR deduction > 100

    FOR i = 0 TO 6 STEP 1
        OUTPUT dayNames[i] + " hours (0-24):"
        DO
            INPUT hours[i]
        WHILE hours[i] < 0 OR hours[i] > 24
        totalhours = totalhours + hours[i]
    END FOR

    maxhours = hours[0]
    FOR i = 1 TO 6 STEP 1
        IF hours[i] > maxhours THEN
            maxhours = hours[i]
            maxDay = i
        END IF
    END FOR

    IF totalhours > 40 THEN
        regularhours = 40
        overtimehours = totalhours - 40
    ELSE
        regularhours = totalhours
        overtimehours = 0
    END IF

    grosspay = regularhours * rate + overtimehours * rate * 1.5
    netpay = grosspay * (1 - deduction / 100)

    CALL printheader()

    accumulated = 0
    FOR i = 0 TO 6 STEP 1
        before = accumulated
        after = before + hours[i]
        regulartoday = 0

        IF before < 40 THEN
            regulartoday = hours[i]
            IF after > 40 THEN
                regulartoday = 40 - before
            END IF
        END IF

        overtimetoday = hours[i] - regulartoday
        daypay = regulartoday * rate + overtimetoday * rate * 1.5
        OUTPUT dayNames[i] + " | " + hours[i] + " | " + daypay
        accumulated = after
    END FOR

    OUTPUT "Total hours: " + totalhours
    OUTPUT "Regular hours: " + regularhours
    OUTPUT "Overtime hours: " + overtimehours
    OUTPUT "Gross pay: " + grosspay
    OUTPUT "Deduction: " + (grosspay - netpay)
    OUTPUT "Net pay: " + netpay
    OUTPUT "Longest working day: " + dayNames[maxDay] + " (" + maxhours + " hours)"
END FUNCTION


FUNCTION printheader
    OUTPUT "WEEKLY TIMESHEET"
    OUTPUT "Day | Hours | Gross(MNT)"
END FUNCTION