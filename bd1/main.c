#include <stdio.h>


#define Days 7 // Number of days in a week
#define normal_limit 40.0 // Normal working hours limit
#define overtime_rate 1.5 // Overtime pay rate

//suutgaliin daraah tsaling bodoh
double calculateNet(double grossPay, double percent) {
    return grossPay * (1.0 - percent / 100.0);// tsever tsalin tootsoh
}

// toon orolt
int main (void) {
    double rate, deduction;//tsagiin tsalin
    double hours[Days];// working hours for each day
    double totalHours = 0.0;// total working hours in a week
    double regularhours, overtimehours; // regular and overtime hours
    double grossPay, netPay; // gross and net pay
    double maxhours; // maximum working hours in a day
    int maxday = 0; // index for maximum working hours
    
    const char *dayNames[Days] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; // huvisagchdiin ner
    
    
    do {
        printf("Hourly rate: ");
        scanf("%lf", &rate);
    } while (rate <=0.0); // validate hourly rate
    
    
    do {
        printf("Deduction percentage: ");
        scanf("%lf", &deduction);
    } while (deduction < 0.0 || deduction > 100.0); // validate deduction percentage

    // doloon udriin ajliin tsag oruulah
    for (int i = 0; i < Days; i++) {// loop through each day of the week to get working hours
        do {
            printf("%s hours (0-24): ", dayNames[i]); // prompt user for working hours for each day
            scanf("%lf", &hours[i]);
        } while (hours[i] < 0.0 || hours[i] > 24.0); // validate working hours
        totalHours += hours[i]; // accumulate total working hours
    }

    // hamgiin ih tsag ajillasan udr
    maxhours = hours[0]; // initialize maximum working hours to the first day's hours
    maxday = 0; // initialize index of the day with maximum working hours to zero
    for (int i = 1; i < Days; i++) { // loop through each day to find the day with maximum working hours
        if (hours[i] > maxhours) {
            maxhours = hours[i]; // update maximum working hours
            maxday = i; // update index of the day with maximum working hours
        }
    }

    // engiin ba iluu tsag
    if (totalHours > normal_limit) { // check if total hours are within normal limit
        regularhours = normal_limit; // regular hours are capped at normal limit
        overtimehours = totalHours - normal_limit; // calculate overtime hours
    } else {
        regularhours = totalHours; // all hours are regular
        overtimehours = 0.0; // no overtime
    }

    // niit ba tsever tsalin
    grossPay = (regularhours * rate) + (overtimehours * rate * overtime_rate); // calculate gross pay
    netPay = calculateNet (grossPay, deduction); // calculate net pay
    
    //husnegtiin garchiga
    printf("\nWeekly time sheet:\n"); // print the weekly time sheet header
    printf("%-12s %10s %12s\n", "Day", "Hours", "Gross Pay"); // print the column headers for the time sheet

    // odriin tsalin tootsoh
    double accumulated = 0.0; // niit ajilsan tsag
    for (int i = 0; i < Days; i++) { // loop through each day to accumulate total hours
        double before = accumulated; // store previous accumulated value
        double after = accumulated + hours[i]; // calculate new accumulated value
        double regulartoday = 0.0; // initialize regular hours for the day to zero

        if (before >= 0 && before < normal_limit) { // check if accumulated hours are below normal limit
            regulartoday = hours[i]; // assume all hours are regular for the day
            

            if (after > normal_limit) { // check if accumulated hours exceed normal limit
                regulartoday = normal_limit - before; // calculate regular hours for the day    
                }
       }
    double overtimeToday = hours[i] - regulartoday; // calculate overtime hours for the day
    double payToday = (regulartoday * rate) + (overtimeToday * rate * overtime_rate); // calculate pay for the day

    //etsiin ur dun
    printf("%-12s %10.2f %12.2f\n", dayNames[i], hours[i], payToday); // print the day, working hours, and pay for the day
    accumulated = after; // update accumulated hours for the next iteration
    }

    printf("\n total hours: %.2lf\n", totalHours); // print total working hours
    printf("Regular hours: %.2lf\n", regularhours); // print total regular hours
    printf("Overtime hours: %.2lf\n", overtimehours); // print total overtime hours
    printf("Gross pay(MNT): %.2lf\n", grossPay); // print total gross pay
    printf("Deduction percentage: %.2lf%%\n", deduction); // print deduction percentage
    printf("Net pay(MNT): %.2lf\n", netPay); // print total net pay
    printf("Longest working day: %.2lf on %s\n", maxhours, dayNames[maxday]); // print the day with maximum working hours
    
    return 0;
}


