/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/*
 * Copyright (C) 2012 Red Hat
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Written by:
 *     System76 <info@system76.com>
 */

#define PAGE_ID "appearance"

#include "config.h"
#include "gis-appearance-page.h"
#include "pop_theme_switcher.h"

struct _GisAppearancePagePrivate {
    PopThemeSwitcher *switcher;
};

typedef struct _GisAppearancePagePrivate GisAppearancePagePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (GisAppearancePage, gis_appearance_page, GIS_TYPE_PAGE);

static void gis_appearance_page_locale_changed (GisPage *page) {
  gis_page_set_title (GIS_PAGE (page), _("Appearance"));
}

static void gis_appearance_page_constructed (GObject *object) {
    GisAppearancePage *page = GIS_APPEARANCE_PAGE (object);
    GisAppearancePagePrivate *priv = gis_appearance_page_get_instance_private (page);

    G_OBJECT_CLASS (gis_appearance_page_parent_class)->constructed (object);

    priv->switcher = pop_theme_switcher_new ();

    GtkWidget *widget = pop_theme_switcher_widget (priv->switcher);
    gtk_widget_set_valign (widget, GTK_ALIGN_START);
    gtk_container_set_border_width (GTK_CONTAINER (widget), 12);

    GtkContainer *container = GTK_CONTAINER (page);
    gtk_container_add (container, widget);
    gtk_widget_show_all (GTK_WIDGET (container));

    gis_page_set_complete (GIS_PAGE (page), TRUE);
}

static void gis_appearance_page_class_init (GisAppearancePageClass *klass) {
    GisPageClass *page_class = GIS_PAGE_CLASS (klass);
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    page_class->page_id = PAGE_ID;
    page_class->locale_changed = gis_appearance_page_locale_changed;

    object_class->constructed = gis_appearance_page_constructed;
}

static void gis_appearance_page_init (GisAppearancePage *page) { }

GisPage * gis_prepare_appearance_page (GisDriver *driver) {
    return g_object_new (GIS_TYPE_APPEARANCE_PAGE, "driver", driver, NULL);
}
