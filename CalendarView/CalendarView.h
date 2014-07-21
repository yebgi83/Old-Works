//
//  CalendarView.h
//  CalendarView
//
//  Created by 이강용 on 12. 10. 9..
//  Copyright (c) 2012년 이강용. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CalendarView : UIView
{
    @private
    NSMutableArray *dayButtons;
}

-(void) onDrawDays:(NSInteger)days StartDow:(NSInteger)startDow CellColor:(UIColor *)cellColor;

@end
