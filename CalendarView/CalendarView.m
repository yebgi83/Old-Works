//
//  CalendarView.m
//  CalendarView
//
//  Created by 이강용 on 12. 10. 9..
//  Copyright (c) 2012년 이강용. All rights reserved.
//

#import "CalendarView.h"

@implementation CalendarView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        // Initialization code
        dayButtons = [NSMutableArray array];
        
        for(NSInteger index = 0; index < 31; index++)
        {
            UIButton *dayButton = [UIButton buttonWithType:UIButtonTypeCustom];
            
            [dayButton setTag:1 + index];
            [dayButton setFrame:CGRectZero];
            [dayButton setTitle:[NSString stringWithFormat:@"%d", dayButton.tag] forState:UIControlStateNormal];
            [dayButton setHidden:NO];
            [dayButtons addObject:dayButton];
            
            [self addSubview:dayButton];
        }
        
        // Draw
        self.backgroundColor = [UIColor clearColor];
        [self setNeedsDisplay];
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
    [self onDrawDays:30 StartDow:3 CellColor:UIColor.blueColor];
}

-(void) onDrawDays:(NSInteger)days StartDow:(NSInteger)startDow CellColor:(UIColor *)cellColor
{
    for(NSInteger index = 0; index < 31; index++)
    {
        if(index < days)
        {
            NSInteger row = (startDow + index) / 7;
            NSInteger cell = (startDow + index) % 7;
        
            CGSize cellSize = CGSizeZero;
            cellSize.width = 60;
            cellSize.height = 60;
        
            CGRect buttonRect = CGRectZero;
            buttonRect.origin = CGPointMake(cellSize.width * cell, cellSize.height * row);
            buttonRect.size = cellSize;

            UIButton *dayButton = [dayButtons objectAtIndex:index];
            [dayButton setFrame:buttonRect];
            [dayButton setTitleColor:cellColor forState:UIControlStateNormal];
            [dayButton setHidden:NO];
        }
        else
        {
            UIButton *dayButton = [dayButtons objectAtIndex:index];
            [dayButton setHidden:YES];
        }
    }
}

@end
