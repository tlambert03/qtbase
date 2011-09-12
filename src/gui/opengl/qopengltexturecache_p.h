/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#ifndef QOPENGLTEXTURECACHE_P_H
#define QOPENGLTEXTURECACHE_P_H

#include <QHash>
#include <QObject>
#include <QtGui/QtGui>
#include <private/qopenglcontext_p.h>
#include <QtCore/qmutex.h>

QT_BEGIN_NAMESPACE

class QOpenGLCachedTexture
{
public:
    QOpenGLCachedTexture(GLuint id, QOpenGLContext *context);
    ~QOpenGLCachedTexture() { m_resource->free(); }

    GLuint id() const { return m_resource->id(); }

private:
    QOpenGLSharedResourceGuard *m_resource;
};

class QOpenGLTextureCache : public QOpenGLSharedResource
{
public:
    static QOpenGLTextureCache *cacheForContext(QOpenGLContext *context);

    QOpenGLTextureCache(QOpenGLContext *);
    ~QOpenGLTextureCache();

    GLuint bindTexture(QOpenGLContext *context, const QPixmap &pixmap);
    GLuint bindTexture(QOpenGLContext *context, const QImage &image);

    void invalidate(qint64 key);

    void invalidateResource();
    void freeResource(QOpenGLContext *ctx);

private:
    GLuint bindTexture(QOpenGLContext *context, qint64 key, const QImage &image);

    QMutex m_mutex;
    QCache<quint64, QOpenGLCachedTexture> m_cache;
};

QT_END_NAMESPACE

#endif

