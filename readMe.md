# HCW Tester
Create and solve tests to study for your sexams.

## Guide
### Step 1: Create a topic
Create a new directory in the program folder with your desired topic name.

### Step 2: Create an exam
Open the directory created in step 1 and create a new textfile with the name of your exam.

### Step 3: Solve your exam
Now open the textfile created in step 2 and add your questions in the following format:

```json
{
    "Question text"
    {
        {"Option 1 text", "Option 1 alternative text"} true
        {"Option 2 text"} false
    }
    Regular
}
```

A **Question** has to contain 1 **String** *text*, an **Array** of 1 **Option** per line and finally a **Type** e.g. *Regular*.

An **Option** has to contain an **Array** of any amount of **String** *text* and a **Boolean** of value *true* or *false*.

## Help
### Commands
[q] = quit
[r] = back
