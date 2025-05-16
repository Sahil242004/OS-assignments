#!/bin/bash

create_db()
{
    echo "create"
    if [ -e std.dat ]  # Fixed spacing issue in the condition
    then
        echo "Database already exists"
    else
        touch std.dat
        echo "Database created successfully"
    fi
}

view_db()
{
    echo "view database"
    if [ -e std.dat ]
    then
        cat std.dat
    else
        echo "Database not yet created"
    fi
}

insert()
{
    echo "insert"
    if [ -e std.dat ]
    then
        echo "Enter the roll no:"
        read roll
        echo "Enter the name:"
        read sName
        echo "Enter marks:"
        read marks
        echo -e "$roll\t$sName\t$marks" >> std.dat
        echo "Record inserted successfully"
    else
        echo "Database does not exist"
    fi
}

delete_record()
{
    echo "delete"
    if [ -e std.dat ]
    then
        echo "Enter the roll no to be deleted:"
        read roll
        count=$(grep -c "^$roll" std.dat)  # Fixed syntax for assignment
        if [ "$count" -eq 0 ]  # Fixed spacing issue in the condition
        then
            echo "Roll number $roll not found"
        else
            grep -v "^$roll" std.dat > std.temp && mv std.temp std.dat  # Fixed file operation
            echo "Record deleted successfully"
        fi
    else
        echo "Database does not exist"
    fi
}

modify_record()
{
    echo "modify"
    if [ -e std.dat ]
    then
        echo "Enter the roll no to be modified:"
        read roll
        count=$(grep -c "^$roll" std.dat)
        if [ "$count" -eq 0 ]
        then
            echo "Roll number $roll not found"
        else
            grep -v "^$roll" std.dat > std.temp
            echo "Enter new name:"
            read newName
            echo "Enter new marks:"
            read newMarks
            echo -e "$roll\t$newName\t$newMarks" >> std.temp
            mv std.temp std.dat
            echo "Record modified successfully"
        fi
    else
        echo "Database does not exist"
    fi
}

display_student()
{
    echo "display result"
    if [ -e std.dat ]
    then
        echo "Enter roll number:"
        read roll
        grep "^$roll" std.dat
        if [ $? -ne 0 ]
        then
            echo "Roll number not found"
        fi
    else
        echo "Database does not exist"
    fi
}

while true
do
    echo "1) Create database"
    echo "2) View database"
    echo "3) Insert record"
    echo "4) Delete record"
    echo "5) Modify record"
    echo "6) Display result of a student"
    echo "7) Exit"
    echo "Enter your choice:"
    read choice

    case $choice in
        1) create_db ;;
        2) view_db ;;
        3) insert ;;
        4) delete_record ;;
        5) modify_record ;;
        6) display_student ;;
        7) exit ;;
        *) echo "Invalid choice, please try again" ;;
    esac
done