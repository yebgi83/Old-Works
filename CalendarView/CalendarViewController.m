//
//  CalendarViewController.m
//  CalendarView
//
//  Created by 이강용 on 12. 10. 9..
//  Copyright (c) 2012년 이강용. All rights reserved.
//

#import "CalendarView.h"
#import "CalendarViewController.h"

@interface CalendarViewController ()

@end

@implementation CalendarViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        // Custom initialization
        [self.view addSubview:[[CalendarView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)]];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
