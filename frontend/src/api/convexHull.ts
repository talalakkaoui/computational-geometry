import type { Point2D, Polygon2D } from '../types'

const API_BASE = import.meta.env.VITE_API_BASE

export async function fetchSlowConvexHull(points: Point2D[]): Promise<Polygon2D> {
  const res = await fetch(`${API_BASE}/api/convex-hull/slow`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ points }),
  })
  const data: { polygon: { vertices: Point2D[]; is_closed: boolean } } = await res.json()
  return { vertices: data.polygon.vertices, isClosed: data.polygon.is_closed }
}

export async function fetchConvexHullGrahamScan(points: Point2D[]): Promise<Polygon2D> {
  const res = await fetch(`${API_BASE}/api/convex-hull/graham-scan`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ points }),
  })
  const data: { polygon: { vertices: Point2D[]; is_closed: boolean } } = await res.json()
  return { vertices: data.polygon.vertices, isClosed: data.polygon.is_closed }
}

export async function fetchConvexHullJarvisMarch(points: Point2D[]): Promise<Polygon2D> {
  const res = await fetch(`${API_BASE}/api/convex-hull/jarvis-march`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ points }),
  })
  const data: { polygon: { vertices: Point2D[]; is_closed: boolean } } = await res.json()
  return { vertices: data.polygon.vertices, isClosed: data.polygon.is_closed }
}