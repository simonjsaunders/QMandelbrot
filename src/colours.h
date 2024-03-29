/*
 * Copyright (c) 2020 Simon J. Saunders
 *
 * This file is part of QMandelbrot.
 *
 * QMandelbrot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QMandelbrot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QMandelbrot.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 *	The colour map for the Mandelbrot set program.
 */

#include <QColor>

#define NUM_COLOURS 240

QRgb colours[NUM_COLOURS] = {
    qRgb(191, 0, 0),     qRgb(204, 0, 0),     qRgb(217, 0, 0),
    qRgb(230, 0, 0),     qRgb(242, 0, 0),     qRgb(255, 0, 0),
    qRgb(255, 26, 26),   qRgb(255, 46, 46),   qRgb(255, 66, 66),
    qRgb(255, 87, 87),   qRgb(255, 107, 107), qRgb(255, 128, 128),
    qRgb(255, 140, 140), qRgb(255, 153, 153), qRgb(255, 166, 166),
    qRgb(255, 203, 166), qRgb(255, 196, 153), qRgb(255, 188, 140),
    qRgb(255, 181, 128), qRgb(255, 169, 107), qRgb(255, 157, 87),
    qRgb(255, 146, 66),  qRgb(255, 134, 46),  qRgb(255, 122, 26),
    qRgb(255, 107, 0),   qRgb(242, 102, 0),   qRgb(230, 96, 0),
    qRgb(217, 91, 0),    qRgb(204, 86, 0),    qRgb(191, 80, 0),
    qRgb(191, 126, 0),   qRgb(204, 135, 0),   qRgb(217, 143, 0),
    qRgb(230, 151, 0),   qRgb(242, 160, 0),   qRgb(255, 168, 0),
    qRgb(255, 177, 26),  qRgb(255, 184, 46),  qRgb(255, 191, 66),
    qRgb(255, 198, 87),  qRgb(255, 205, 107), qRgb(255, 212, 128),
    qRgb(255, 216, 140), qRgb(255, 220, 153), qRgb(255, 225, 166),
    qRgb(255, 241, 166), qRgb(255, 239, 153), qRgb(255, 237, 140),
    qRgb(255, 235, 128), qRgb(255, 231, 107), qRgb(255, 228, 87),
    qRgb(255, 225, 66),  qRgb(255, 222, 46),  qRgb(255, 218, 26),
    qRgb(255, 214, 0),   qRgb(242, 203, 0),   qRgb(230, 193, 0),
    qRgb(217, 182, 0),   qRgb(204, 171, 0),   qRgb(191, 161, 0),
    qRgb(176, 191, 0),   qRgb(188, 204, 0),   qRgb(199, 217, 0),
    qRgb(211, 230, 0),   qRgb(223, 242, 0),   qRgb(235, 255, 0),
    qRgb(237, 255, 26),  qRgb(238, 255, 46),  qRgb(240, 255, 66),
    qRgb(242, 255, 87),  qRgb(243, 255, 107), qRgb(245, 255, 128),
    qRgb(246, 255, 140), qRgb(247, 255, 153), qRgb(248, 255, 166),
    qRgb(221, 255, 166), qRgb(216, 255, 153), qRgb(211, 255, 140),
    qRgb(207, 255, 128), qRgb(199, 255, 107), qRgb(191, 255, 87),
    qRgb(183, 255, 66),  qRgb(176, 255, 46),  qRgb(168, 255, 26),
    qRgb(158, 255, 0),   qRgb(150, 242, 0),   qRgb(142, 230, 0),
    qRgb(134, 217, 0),   qRgb(126, 204, 0),   qRgb(119, 191, 0),
    qRgb(4, 191, 0),     qRgb(4, 204, 0),     qRgb(4, 217, 0),
    qRgb(5, 230, 0),     qRgb(5, 242, 0),     qRgb(5, 255, 0),
    qRgb(30, 255, 26),   qRgb(50, 255, 46),   qRgb(70, 255, 66),
    qRgb(90, 255, 87),   qRgb(110, 255, 107), qRgb(130, 255, 128),
    qRgb(143, 255, 140), qRgb(155, 255, 153), qRgb(168, 255, 166),
    qRgb(166, 255, 228), qRgb(153, 255, 224), qRgb(140, 255, 221),
    qRgb(128, 255, 217), qRgb(107, 255, 211), qRgb(87, 255, 205),
    qRgb(66, 255, 198),  qRgb(46, 255, 192),  qRgb(26, 255, 186),
    qRgb(0, 255, 179),   qRgb(0, 242, 170),   qRgb(0, 230, 161),
    qRgb(0, 217, 152),   qRgb(0, 204, 143),   qRgb(0, 191, 134),
    qRgb(0, 168, 191),   qRgb(0, 180, 204),   qRgb(0, 191, 217),
    qRgb(0, 202, 230),   qRgb(0, 213, 242),   qRgb(0, 224, 255),
    qRgb(26, 227, 255),  qRgb(46, 230, 255),  qRgb(66, 232, 255),
    qRgb(87, 235, 255),  qRgb(107, 237, 255), qRgb(128, 240, 255),
    qRgb(140, 241, 255), qRgb(153, 243, 255), qRgb(166, 244, 255),
    qRgb(166, 212, 255), qRgb(153, 206, 255), qRgb(140, 200, 255),
    qRgb(128, 194, 255), qRgb(107, 184, 255), qRgb(87, 174, 255),
    qRgb(66, 164, 255),  qRgb(46, 155, 255),  qRgb(26, 145, 255),
    qRgb(0, 133, 255),   qRgb(0, 126, 242),   qRgb(0, 119, 230),
    qRgb(0, 113, 217),   qRgb(0, 106, 204),   qRgb(0, 99, 191),
    qRgb(0, 8, 191),     qRgb(0, 8, 204),     qRgb(0, 9, 217),
    qRgb(0, 9, 230),     qRgb(0, 10, 242),    qRgb(0, 10, 255),
    qRgb(26, 35, 255),   qRgb(46, 54, 255),   qRgb(66, 74, 255),
    qRgb(87, 93, 255),   qRgb(107, 113, 255), qRgb(128, 133, 255),
    qRgb(140, 145, 255), qRgb(153, 157, 255), qRgb(166, 169, 255),
    qRgb(210, 166, 255), qRgb(204, 153, 255), qRgb(198, 140, 255),
    qRgb(191, 128, 255), qRgb(181, 107, 255), qRgb(171, 87, 255),
    qRgb(161, 66, 255),  qRgb(150, 46, 255),  qRgb(140, 26, 255),
    qRgb(128, 0, 255),   qRgb(121, 0, 242),   qRgb(115, 0, 230),
    qRgb(108, 0, 217),   qRgb(102, 0, 204),   qRgb(96, 0, 191),
    qRgb(153, 0, 191),   qRgb(163, 0, 204),   qRgb(173, 0, 217),
    qRgb(184, 0, 230),   qRgb(194, 0, 242),   qRgb(204, 0, 255),
    qRgb(209, 26, 255),  qRgb(213, 46, 255),  qRgb(217, 66, 255),
    qRgb(221, 87, 255),  qRgb(225, 107, 255), qRgb(230, 128, 255),
    qRgb(232, 140, 255), qRgb(235, 153, 255), qRgb(237, 166, 255),
    qRgb(255, 166, 251), qRgb(255, 153, 251), qRgb(255, 140, 250),
    qRgb(255, 128, 250), qRgb(255, 107, 249), qRgb(255, 87, 248),
    qRgb(255, 66, 247),  qRgb(255, 46, 247),  qRgb(255, 26, 246),
    qRgb(255, 0, 245),   qRgb(242, 0, 233),   qRgb(230, 0, 220),
    qRgb(217, 0, 208),   qRgb(204, 0, 196),   qRgb(191, 0, 184),
    qRgb(191, 0, 126),   qRgb(204, 0, 135),   qRgb(217, 0, 143),
    qRgb(230, 0, 151),   qRgb(242, 0, 160),   qRgb(255, 0, 168),
    qRgb(255, 26, 177),  qRgb(255, 46, 184),  qRgb(255, 66, 191),
    qRgb(255, 87, 198),  qRgb(255, 107, 205), qRgb(255, 128, 212),
    qRgb(255, 140, 216), qRgb(255, 153, 220), qRgb(255, 166, 225),
    qRgb(255, 166, 198), qRgb(255, 153, 190), qRgb(255, 140, 182),
    qRgb(255, 128, 173), qRgb(255, 107, 160), qRgb(255, 87, 147),
    qRgb(255, 66, 134),  qRgb(255, 46, 121),  qRgb(255, 26, 108),
    qRgb(255, 0, 92),    qRgb(242, 0, 87),    qRgb(230, 0, 83),
    qRgb(217, 0, 78),    qRgb(204, 0, 73),    qRgb(191, 0, 69)};
